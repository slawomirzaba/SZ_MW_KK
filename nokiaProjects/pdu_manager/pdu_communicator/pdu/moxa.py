from pysnmp.proto import rfc1902
from pdu_communicator.pdu.pdu import PDU


class MOXA(PDU):
    """Class provides attributes and private methods to manage a PDU of type MOXA."""

    def __init__(self, host, timeout=10):
        """
        :param string host:         IP address or domain name of the MOXA device.
        :param float timeout:       Maximum number of seconds to wait for expected pdu outlet status.
        """
        super(MOXA, self).__init__(host, timeout)

        self._outlet_status_value = {"off": '1', "on": '0'}
        self._community = 'private'
        self._version = 1
        self._key = '.1.3.6.1.4.1.8691.10.2214.10.2.1.4'

    def _set_oid_value(self, action, **kwargs):
        return rfc1902.Integer(self._outlet_status_value[action])

    def _build_snmp_oid(self, outlet):
        return '{}.{}'.format(self._key, outlet-1)