
#include "mxml.h"


void AppendXMLData(mxml_node_t *d, mxml_node_t *node) {

    mxml_node_t *xml;
    mxml_node_t *body;
    uint32_t count = 0;
    const char *field;

    if ((field = mxmlElementGetAttr(d, "count"))) {
        count = atoi(field);
    }

    mxmlElementSetAttrf(d, "count", "%d", ++count);

    xml = mxmlFindElement(d, d, "ParameterList", NULL, NULL, MXML_DESCEND);
    mxmlElementSetAttrf(xml, "soap-enc:arrayType", "cwmp:ParameterValueStruct[%d]", count);
    xml = mxmlNewElement(xml, "ParameterValueStruct");

    body = mxmlNewElement(xml, "Name");
    mxmlNewText(body, 0, mxmlGetText(node, 0));

    body = mxmlNewElement(xml, "Value");
    mxmlNewText(body, 0, "AA");
    mxmlElementSetAttr(body, "xsi:type", "xsd:boolean");
}

void element_cb(mxml_node_t *node, mxml_sax_event_t event, void *data) {

    mxml_node_t *d = data;
    mxml_node_t *xml;
    mxml_node_t *header;
    mxml_node_t *header_child;
    mxml_node_t *parent;
    mxml_node_t *body;
    const char *field;
    const char *prevfield;
    const char *name;
    uint32_t count;
    uint32_t i;

    switch (event) {
    case MXML_SAX_ELEMENT_OPEN:

        field = mxmlGetElement(node);

        if ((strstr(field, ":Envelope"))) {
            count = mxmlElementGetAttrCount(node);

            for (i = 0; i < count; i++) {
                prevfield = mxmlElementGetAttrByIndex(node, i, &name);
                mxmlElementSetAttr(d, name, prevfield);
            }
        }

        // } else if ((prevfield = mxmlElementGetAttr(d, "field")))
        //     mxmlElementSetAttrf(d, "field", "%s-%s", prevfield, field);
        // else
        //     mxmlElementSetAttr(d, "field", field);

        break;
    case MXML_SAX_DATA:
        // field = mxmlElementGetAttr(d, "field");
        // mxmlElementDeleteAttr(d, "field");

        header_child = mxmlGetParent(node);
        name = mxmlGetElement(header_child);

        if (strstr(name, ":ID")) {
            header = mxmlGetParent(header_child);
            xml = mxmlNewElement(d, mxmlGetElement(header));
            xml = mxmlNewElement(xml, mxmlGetElement(header_child));

            count = mxmlElementGetAttrCount(header_child);

            for (i = 0; i < count; i++) {
                prevfield = mxmlElementGetAttrByIndex(header_child, i, &name);
                mxmlElementSetAttr(xml, name, prevfield);
            }

            mxmlNewText(xml, 0, mxmlGetText(node, 0));

        // } else if (strstr(field, "soapenv:Body")) {

            // xml = mxmlNewElement(d, "soap:Body");

            // if (strstr(field, "GetParameterValues")) {
            //     body = mxmlNewElement(xml, "cwmp:GetParameterValuesResponse");

            //     body = mxmlNewElement(body, "ParameterList");

            //     AppendXMLData(d, node);
            // } else if (strstr(field, "SetParameterValues"))
            //     body = mxmlNewElement(xml, "cwmp:SetParameterValuesResponse");

        }  else if (!strcmp("string", name)) {
            header = mxmlGetParent(header_child);
            parent = mxmlGetParent(header);
            name = mxmlGetElement(parent);

            if (!strcmp("cwmp:GetParameterValues", name)) {

                if (!mxmlElementGetAttr(d, "body")) {
                    mxmlElementSetAttr(d, "body", "1");
                    xml = mxmlNewElement(d, "soap:Body");
                    body = mxmlNewElement(xml, "cwmp:GetParameterValuesResponse");
                    body = mxmlNewElement(body, "ParameterList");
                }

                AppendXMLData(d, node);
            }
        }
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{

    const char *xmldata = "<soapenv:Envelope soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:cwmp=\"urn:dslforum-org:cwmp-1-0\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/encoding/\"><soapenv:Header><cwmp:ID soapenv:mustUnderstand=\"1\" xsi:type=\"xsd:string\">1449BC177008:1681374896884</cwmp:ID></soapenv:Header><soapenv:Body><cwmp:GetParameterValues xmlns:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><ParameterNames soap:arrayType=\"xsd:string[20]\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/encoding/\"><string>InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Enable</string><string>InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Status</string><string>InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</string><string>InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.DHCPServerEnable</string><string>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</string><string>InternetGatewayDevice.LANDevice.2.LANEthernetInterfaceConfig.1.Enable</string><string>InternetGatewayDevice.LANDevice.2.LANEthernetInterfaceConfig.1.Status</string><string>InternetGatewayDevice.LANDevice.2.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</string><string>InternetGatewayDevice.LANDevice.2.LANHostConfigManagement.DHCPServerEnable</string><string>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</string><string>InternetGatewayDevice.LANDevice.3.LANEthernetInterfaceConfig.1.Enable</string><string>InternetGatewayDevice.LANDevice.3.LANEthernetInterfaceConfig.1.Status</string><string>InternetGatewayDevice.LANDevice.3.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</string><string>InternetGatewayDevice.LANDevice.3.LANHostConfigManagement.DHCPServerEnable</string><string>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</string><string>InternetGatewayDevice.LANDevice.4.LANEthernetInterfaceConfig.1.Enable</string><string>InternetGatewayDevice.LANDevice.4.LANEthernetInterfaceConfig.1.Status</string><string>InternetGatewayDevice.LANDevice.4.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</string><string>InternetGatewayDevice.LANDevice.4.LANHostConfigManagement.DHCPServerEnable</string><string>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</string></ParameterNames></cwmp:GetParameterValues></soapenv:Body></soapenv:Envelope>";

// <soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:soap-enc="http://schemas.xmlsoap.org/soap/encoding/" xmlns:cwmp="urn:dslforum-org:cwmp-1-0" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"><soap:Header><cwmp:ID soap:mustUnderstand="1">1449BC177008:1681374896884</cwmp:ID></soap:Header><soap:Body><cwmp:GetParameterValuesResponse><ParameterList soap-enc:arrayType="cwmp:ParameterValueStruct[20]"><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Enable</Name><Value xsi:type="xsd:boolean">1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Status</Name><Value xsi:type="xsd:string">Up</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</Name><Value xsi:type="xsd:string">192.168.1.1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.DHCPServerEnable</Name><Value xsi:type="xsd:boolean">1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</Name><Value xsi:type="xsd:string">FE80::6EEB:9525:8AD4:A30B/64</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.2.LANEthernetInterfaceConfig.1.Enable</Name><Value xsi:type="xsd:boolean">0</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.2.LANEthernetInterfaceConfig.1.Status</Name><Value xsi:type="xsd:string">Down</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.2.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</Name><Value xsi:type="xsd:string">192.168.2.1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.2.LANHostConfigManagement.DHCPServerEnable</Name><Value xsi:type="xsd:boolean">1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</Name><Value xsi:type="xsd:string">FE80::6EEB:9525:8AD4:A30B/64</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.3.LANEthernetInterfaceConfig.1.Enable</Name><Value xsi:type="xsd:boolean">0</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.3.LANEthernetInterfaceConfig.1.Status</Name><Value xsi:type="xsd:string">Down</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.3.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</Name><Value xsi:type="xsd:string">192.168.3.1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.3.LANHostConfigManagement.DHCPServerEnable</Name><Value xsi:type="xsd:boolean">1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</Name><Value xsi:type="xsd:string">FE80::6EEB:9525:8AD4:A30B/64</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.4.LANEthernetInterfaceConfig.1.Enable</Name><Value xsi:type="xsd:boolean">0</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.4.LANEthernetInterfaceConfig.1.Status</Name><Value xsi:type="xsd:string">Down</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.4.LANHostConfigManagement.IPInterface.1.IPInterfaceIPAddress</Name><Value xsi:type="xsd:string">192.168.4.1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.LANDevice.4.LANHostConfigManagement.DHCPServerEnable</Name><Value xsi:type="xsd:boolean">1</Value></ParameterValueStruct><ParameterValueStruct><Name>InternetGatewayDevice.X_00507F_Status.LAN.IPv6.IPAddress</Name><Value xsi:type="xsd:string">FE80::6EEB:9525:8AD4:A30B/64</Value></ParameterValueStruct></ParameterList></cwmp:GetParameterValuesResponse></soap:Body></soap:Envelope>


    mxml_node_t *tree, *xml, *list;

    // tree = mxmlSAXLoadString(NULL, xmldata, MXML_TEXT_CALLBACK, element_cb, NULL);
    // mxmlDelete(tree);

    mxmlSetWrapMargin(0);

    xml = mxmlNewElement(NULL, "soap:Envelope");
    // mxmlElementSetAttr(xml, "xmlns:soap", "http://schemas.xmlsoap.org/soap/envelope/");
    // mxmlElementSetAttr(xml, "xmlns:soap-enc", "http://schemas.xmlsoap.org/soap/encoding/");
    // mxmlElementSetAttr(xml, "xmlns:cwmp", "urn:dslforum-org:cwmp-1-0");
    // mxmlElementSetAttr(xml, "xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    // mxmlElementSetAttr(xml, "xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");


    tree = mxmlSAXLoadString(NULL, xmldata, MXML_TEXT_CALLBACK, element_cb, xml);

    mxmlElementDeleteAttr(xml, "body");
    mxmlElementDeleteAttr(xml, "count");

    mxmlDelete(tree);

    // header = mxmlNewElement(xml, "soap:Header");
    // header = mxmlNewElement(header, "cwmp:ID");
    // mxmlElementSetAttr(header, "soap:mustUnderstand", "1");
    // mxmlNewText(header, 0, "1449BC177008:1681374896884");

    // header = mxmlNewElement(xml, "soap:Body");
    // header = mxmlNewElement(header, "cwmp:GetParameterValuesResponse");
    // header = mxmlNewElement(header, "ParameterList");

    // body = mxmlNewElement(header, "ParameterValueStruct");

    // data = mxmlNewElement(body, "Name");
    // mxmlNewText(data, 0, "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Enable");
    // data = mxmlNewElement(body, "Value");
    // mxmlElementSetAttr(data, "xsi:type", "xsd:boolean");
    // mxmlNewInteger(data, 1);

    // data = mxmlNewElement(body, "Name");
    // mxmlNewText(data, 0, "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Status");
    // data = mxmlNewElement(body, "Value");
    // mxmlElementSetAttr(data, "xsi:type", "xsd:string");
    // mxmlNewText(data, 0, "Up");

    // mxmlElementSetAttrf(header, "soap-enc:arrayType", "cwmp:ParameterValueStruct[%d]", 2);


    // char buf[1000];
    // uint32_t len = mxmlSaveString(xml, buf, sizeof(buf), MXML_NO_CALLBACK);
//    char *buf = mxmlSaveAllocString(xml, MXML_NO_CALLBACK);

//    char *buf = mxmlSaveAllocString(xml, MXML_NO_CALLBACK);
    char *buf;
    if ((buf = malloc(101))) {
        uint32_t len = mxmlSaveString(xml, buf, 100, MXML_NO_CALLBACK);

        if (len > 100 && (buf = realloc(buf, len + 1))) {
            mxmlSaveString(xml, buf, len, MXML_NO_CALLBACK);
        }

        printf("%d buf=%s\n", len, buf);

        free(buf);
    }

    mxmlDelete(xml);

    return 0;
}
