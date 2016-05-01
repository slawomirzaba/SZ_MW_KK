from pysnmp.proto import rfc1902
from pdu_communicator.pdu.pdu import PDU

class ATEN(PDU):
    """Class provides attributes and private methods to manage a PDU of type ATEN."""

    def __init__(self, host, timeout=10):
        """
        :param string host:         IP address or domain name of the ATEN device.
        :param float timeout:       Maximum number of seconds to wait for expected pdu outlet status.
        """
        super(ATEN, self).__init__(host, timeout)

        self._outlet_status_value = {"off": "1", "on": "2"}
        self._community = "administrator"
        self._version = 1
        self._key = '.1.3.6.1.4.1.21317.1.3.2.2.2.2'

    def _set_oid_value(self, action, **kwargs):
        return rfc1902.Integer(self._outlet_status_value[action])

    def _build_snmp_oid(self, outlet):
        return '{0}.{1}.0'.format(self._key, outlet + 1)
