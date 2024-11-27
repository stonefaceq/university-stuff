package org.example.parsers;

import org.example.models.Gun;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.util.List;
import java.util.logging.Logger;

public class SAXXMLParser extends XMLParser {
    private static final Logger logger = Logger.getLogger(SAXXMLParser.class.getName());

    private final SAXParser parser;
    private final GunsHandler handler;

    public SAXXMLParser() throws ParserConfigurationException, SAXException {
        parser = SAXParserFactory.newInstance().newSAXParser();
        handler = new GunsHandler();
        logger.info("SAXXMLParser initialized with new SAXParser and GunsHandler.");
    }

    @Override
    public List<Gun> parse(String path) {
        logger.info("Parsing XML file: " + path);
        try {
            parser.parse(path, handler);
            logger.info("Successfully parsed XML file: " + path);
            return handler.getGuns();
        } catch (SAXException | IOException e) {
            logger.severe("Error occurred during XML parsing: " + e.getMessage());
            throw new RuntimeException(e);
        }
    }
}
