from pysnmp.entity.rfc3413.oneliner import cmdgen
from abc import ABCMeta, abstractmethod
import time


class PDU(object):
    """PDU is a class that makes it possible to manage a single PDU device over the SNMP protocol.
    Class provides the on, off, reset, and get_status methods.
    """

    __metaclass__ = ABCMeta

    def __init__(self, host, timeout):
        """
        :param string host:     IP address or domain name of PDU device.
        :param float timeout:   Maximum number of seconds to wait for expected pdu outlet status.
        """
        self._host = host
        self._version = None
        self._community = None
        self._outlet_status_value = {}
        self._timeout = timeout
        self._cmdgen = cmdgen.CommandGenerator()

    def _execute_get_cmd(self, snmp_msg, **kwargs):
        community_data = cmdgen.CommunityData('my-agent', self._community, self._version)
        udp_transport = cmdgen.UdpTransportTarget((self._host, 161))
        error_indication, error_status, error_index, var_binds = \
            self._cmdgen.getCmd(community_data, udp_transport, snmp_msg)

        if error_indication:
            print error_indication

        else:
            if error_status:
                print "GetRequest message: {0} at {1}".format( error_status.prettyPrint(), 
                      error_index and var_binds[int(error_index) - 1] or "?" )

            else:
                proper_var_bind = str(var_binds[0][1])
                return proper_var_bind

    def _execute_set_cmd(self, action, snmp_msg, **kwargs):
        community_data = cmdgen.CommunityData('my-agent', self._community, self._version)
        udp_transport = cmdgen.UdpTransportTarget((self._host, 161))
        outlets_value = self._set_oid_value(action, **kwargs)
        error_indication, error_status, error_index, var_binds = \
            self._cmdgen.setCmd(community_data, udp_transport, (snmp_msg, outlets_value))

        if error_indication:
            print error_indication

        else:
            if error_status:
                print "SetRequest message: {0} at {1}".format( error_status.prettyPrint(), 
                      error_index and var_binds[int(error_index) - 1] or "?" )

    def set_outlet_value(self, outlet, action):
        """Set pdu outlet status.
        :param string action:       Action (on/off) to be applied on pdu outlet.
        :param integer outlet:      Pdu outlet to be turned on.
        """
        snmp_msg = self._build_snmp_oid(outlet=outlet)
        self._execute_set_cmd(action, snmp_msg, outlet=outlet)
        self._check_outlet_value(action, snmp_msg, outlet=outlet)

    def get_outlet_status(self, outlet):
        """Get Pdu outlet status.

        :param integer outlet:      Pdu outlet whose status should be returned.

        :return:                    Pdu outlet status.
        :rtype:                     string
        """
        snmp_msg = self._build_snmp_oid(outlet=outlet)

        try:
            reversed_dict = dict((value, key) for key, value in self._outlet_status_value.iteritems())
            final_index = self._execute_get_cmd(snmp_msg, outlet=outlet)
            return reversed_dict[final_index]
        except KeyError:
            print "Outlet {} has invalid status".format(outlet)

    @abstractmethod
    def _set_oid_value(self, action, **kwargs):
        """ Set oid value"""

    @abstractmethod
    def _build_snmp_oid(self, outlet):
        """ Build snmp oid"""

    def _check_outlet_value(self, action, snmp_msg, **kwargs):
        start = time.time()

        while time.time() - start < self._timeout:
            outlet_value = self._execute_get_cmd(snmp_msg, **kwargs)
            if outlet_value == self._outlet_status_value[action]:
                return True
            time.sleep(2)
        #print "Action ({0}) on {1} was not possible.".format(action, self._host)
