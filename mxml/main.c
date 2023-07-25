
#include "mxml.h"


struct xmltrees {
    mxml_node_t *main;
    mxml_node_t *child;
} typedef xmltrees_t;


void AppendXMLData(mxml_node_t *d, mxml_node_t *node) {

    mxml_node_t *xml;
    mxml_node_t *body;
    // uint32_t count = 0;
    // const char *field;

    // if ((field = mxmlElementGetAttr(d, "count"))) {
    //     count = atoi(field);
    // }

    // mxmlElementSetAttrf(d, "count", "%d", ++count);

    // xml = mxmlFindElement(d, d, "ParameterList", NULL, NULL, MXML_DESCEND);
    // mxmlElementSetAttrf(xml, "soap-enc:arrayType", "cwmp:ParameterValueStruct[%d]", count);
    xml = mxmlNewElement(d, "ParameterValueStruct");

    body = mxmlNewElement(xml, "Name");
    mxmlNewText(body, 0, mxmlGetText(node, 0));

    body = mxmlNewElement(xml, "Value");
    mxmlNewText(body, 0, "AA");
    mxmlElementSetAttr(body, "xsi:type", "xsd:boolean");

}



void element_cb(mxml_node_t *node, mxml_sax_event_t event, void *data) {

    mxml_node_t *d = ((xmltrees_t *)data)->main;
    mxml_node_t *dchild = ((xmltrees_t *)data)->child;
    mxml_node_t *xml;
    mxml_node_t *header;
    mxml_node_t *header_child;
    mxml_node_t *parent;
    mxml_node_t *body;
    const char *field;
    const char *prevfield;
    const char *name;
    unsigned int count;
    unsigned int i;

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

        }  else if (!strcmp("string", name)) {
            header = mxmlGetParent(header_child);
            parent = mxmlGetParent(header);
            name = mxmlGetElement(parent);

            if (!strcmp("cwmp:GetParameterValues", name)) {

                // if (!mxmlElementGetAttr(d, "body")) {

                //     mxmlElementSetAttr(d, "body", "1");
                //     xml = mxmlNewElement(d, "soap:Body");
                //     body = mxmlNewElement(xml, "cwmp:GetParameterValuesResponse");
                //     body = mxmlNewElement(body, "ParameterList");
                // }

                if (!(body = mxmlFindElement(dchild, dchild, "ParameterList", NULL, NULL, MXML_DESCEND))) {
                    body = mxmlNewElement(dchild, "cwmp:GetParameterValuesResponse");
                    body = mxmlNewElement(body, "ParameterList");
                }

                AppendXMLData(body, node);
                mxmlRetain(dchild);

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


    mxml_node_t *tree;
    mxml_node_t *body;
    xmltrees_t xml;

    // tree = mxmlSAXLoadString(NULL, xmldata, MXML_TEXT_CALLBACK, element_cb, NULL);
    // mxmlDelete(tree);

    mxmlSetWrapMargin(0);

    // for (int i = 0; i < 10000; i++) {

    xml.main = mxmlNewElement(NULL, "soap:Envelope");

    xml.child = mxmlNewElement(NULL, "soap:Body");


    tree = mxmlSAXLoadString(NULL, xmldata, MXML_TEXT_CALLBACK, element_cb, &xml);

    // mxmlSetInteger(xml, 10);

    // mxmlElementDeleteAttr(xml->main, "body");
    // mxmlElementDeleteAttr(xml->main, "count");

    mxmlDelete(tree);

    char *buf;
    if ((buf = malloc(101))) {

        tree = mxmlFindElement(xml.child, xml.child, "ParameterList", NULL, NULL, MXML_DESCEND);
        mxmlElementSetAttrf(tree, "soap-enc:arrayType", "cwmp:ParameterValueStruct[%d]", mxmlGetRefCount(xml.child) - 1);

        mxmlAdd(xml.main, 1, NULL, xml.child);

        unsigned int len = mxmlSaveString(xml.main, buf, 100, MXML_NO_CALLBACK);

        if (len > 100 && (buf = realloc(buf, len + 1))) {
            mxmlSaveString(xml.main, buf, len, MXML_NO_CALLBACK);
        }

        printf("%d buf=%s\n", len, buf);

        free(buf);


        // len = mxmlSaveString((xml->child), buf, 100, MXML_NO_CALLBACK);

        // if (len > 100 && (buf = realloc(buf, len + 1))) {
        //     mxmlSaveString(xml->child, buf, len, MXML_NO_CALLBACK);
        // }

        // printf("%d buf=%s\n", len, buf);

        // free(buf);


    }
    mxmlDelete(xml.child);
    mxmlDelete(xml.main);

    // }

    return 0;
}
