from pysnmp.proto import rfc1902
from pdu_communicator.pdu.pdu import PDU


class DCS(PDU):
    """Class provides attributes and private methods to manage DCSmart PDU."""

    def __init__(self, host, timeout=10, **kwargs):
        """
        :param string host:         IP address or domain name of the DC Smart device.
        :param float timeout:       Maximum number of seconds to wait for expected pdu outlet status.
        """
        super(DCS, self).__init__(host, timeout)

        self._outlet_status_value = {"off": '1', "on": '2'}
        self._community = 'dcsrRW'
        self._version = 0
        self._key = '.1.3.6.1.4.1.11923.2.1.2.1.6.1'

    def _set_oid_value(self, action, **kwargs):
        return rfc1902.Integer(self._outlet_status_value[action])

    def _build_snmp_oid(self, outlet):
        bank, outlet = self._extract_bank_and_outlet_number(outlet)
        return '{oid}.{action_value}.{bank}.{outlet}'.format(oid=self._key, action_value=8, bank=bank,  outlet=outlet)

    def _extract_bank_and_outlet_number(self, outlet):
        return ((outlet / 10)-1), ((outlet % 10)-1)

    def _execute_get_cmd(self, snmp_msg, **kwargs):
        return PDU._execute_get_cmd(self, self._change_snmp_msg_to_get_state(snmp_msg))

    def _change_snmp_msg_to_get_state(self, set_snmp_msg):
        return '{oid}.{action_value}.{bank}.{outlet}'.format(oid=self._key, action_value=4, bank=set_snmp_msg[-3],
                                                             outlet=set_snmp_msg[-1])
