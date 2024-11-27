package org.example.parsers;

import org.example.models.Gun;
import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.logging.Logger;

public abstract class XMLParser {
    private static final Logger logger = Logger.getLogger(XMLParser.class.getName());

    abstract public List<Gun> parse(String xmlPath);

    public List<Gun> parse(String xmlPath, String xsdPath) {
        if (validate(xmlPath, xsdPath)) {
            logger.info("XML file is valid, starting parsing.");
            return parse(xmlPath);
        } else {
            logger.warning("XML validation failed, cannot parse the file.");
            return null;
        }
    }

    protected boolean validate(String xmlPath, String xsdPath) {
        try {
            logger.info("Starting XML validation for file: " + xmlPath + " with schema: " + xsdPath);
            SchemaFactory factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = factory.newSchema(new File(xsdPath));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(new File(xmlPath)));
            logger.info("XML file " + xmlPath + " is successfully validated against schema " + xsdPath);
        } catch (SAXException | IOException e) {
            logger.severe("Error during XML validation: " + e.getMessage());
            return false;
        }
        return true;
    }
}
