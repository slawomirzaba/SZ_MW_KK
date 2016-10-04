from pysnmp.proto import rfc1902
from pdu_communicator.pdu.pdu import PDU


class BBOX(PDU):
    """Class provides attributes and private methods to manage BlackBox PDU."""

    def __init__(self, host, timeout=10, **kwargs):
        """
        :param string host:         IP address or domain name of the BlackBox device.
        :param float timeout:       Maximum number of seconds to wait for expected pdu outlet status.
        """
        super(BBOX, self).__init__(host, timeout)

        self._outlet_status_value = {"off": '6', "on": '5'}
        self._community = 'private'
        self._version = 1
        self._key = '.1.3.6.1.4.1.2634.3.100.200.1'

    def _set_oid_value(self, action, **kwargs):
        return rfc1902.Integer(self._outlet_status_value[action])

    def _build_snmp_oid(self, outlet):
        return '{}.4.{}'.format(self._key, outlet)

    def _execute_get_cmd(self, snmp_msg, **kwargs):
        get_value = PDU._execute_get_cmd(self, self._change_snmp_msg_to_get_state(snmp_msg))
        return self._translate_get_to_set_snmp_value(get_value)

    def _change_snmp_msg_to_get_state(self, set_snmp_msg):
        return '{oid}.{action_value}.{outlet}'.format(oid=self._key, action_value=3, outlet=set_snmp_msg[-1])

    def _translate_get_to_set_snmp_value(self, get_value):
        values = {'1': '5', '0': '6'}
        set_value = values[get_value]
        return set_value