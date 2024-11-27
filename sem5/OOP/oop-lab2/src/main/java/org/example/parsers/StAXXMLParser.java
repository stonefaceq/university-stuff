package org.example.parsers;

import org.example.models.Gun;
import org.example.models.TTC;

import javax.xml.namespace.QName;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

public class StAXXMLParser extends XMLParser {
    private static final Logger logger = Logger.getLogger(StAXXMLParser.class.getName());
    private Gun gun;

    @Override
    public List<Gun> parse(String path) {
        try {
            logger.info("Starting parsing of XML file: " + path);
            XMLEventReader reader = XMLInputFactory.newInstance().createXMLEventReader(new FileInputStream(path));
            List<Gun> guns = new ArrayList<>();

            while (reader.hasNext()) {
                XMLEvent event = reader.nextEvent();

                if (event.isStartDocument()) {
                    startDocument(event, reader, guns);
                } else if (event.isStartElement()) {
                    startElement(event, reader, guns);
                } else if (event.isEndElement()) {
                    endElement(event, reader, guns);
                } else if (event.isEndDocument()) {
                    endDocument(event, reader, guns);
                }
            }

            logger.info("Finished parsing XML file: " + path);
            return guns;
        } catch (XMLStreamException | FileNotFoundException e) {
            logger.severe("Error occurred during XML parsing: " + e.getMessage());
            throw new RuntimeException(e);
        }
    }

    private void startDocument(XMLEvent event, XMLEventReader reader, List<Gun> guns) {
        // Optional: log document start if needed
        logger.fine("Start of XML document.");
    }

    private void startElement(XMLEvent event, XMLEventReader reader, List<Gun> guns) throws XMLStreamException {
        StartElement element = event.asStartElement();
        switch (element.getName().getLocalPart()) {
            case Gun.MODEL -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.setModel(data);
                logger.fine("Set Gun Model: " + data);
            }
            case Gun.HANDY -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.setHandy(data);
                logger.fine("Set Gun Handy: " + data);
            }
            case Gun.ORIGIN -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.setOrigin(data);
                logger.fine("Set Gun Origin: " + data);
            }
            case Gun.MATERIAL -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.setMaterial(data);
                logger.fine("Set Gun Material: " + data);
            }
            case TTC.FIRING_RANGE -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.getTtc().setFiringRange(data);
                logger.fine("Set TTC Firing Range: " + data);
            }
            case TTC.SIGHTING_RANGE -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.getTtc().setSightingRange(data);
                logger.fine("Set TTC Sighting Range: " + data);
            }
            case TTC.MAGAZINE -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.getTtc().setMagazine(data);
                logger.fine("Set TTC Magazine: " + data);
            }
            case TTC.SIGHT -> {
                event = reader.nextEvent();
                String data = event.asCharacters().getData();
                gun.getTtc().setSight(data);
                logger.fine("Set TTC Sight: " + data);
            }
            case Gun.GUN -> {
                gun = new Gun();
                gun.setTtc(new TTC());
                String data = element.getAttributeByName(QName.valueOf(Gun.ID)).getValue();
                gun.setId(data);
                logger.fine("Created new Gun with ID: " + data);
            }
        }
    }

    private void endElement(XMLEvent event, XMLEventReader reader, List<Gun> guns) {
        EndElement element = event.asEndElement();
        String name = element.getName().getLocalPart();
        if (name.equals(Gun.GUN) && gun != null) {
            guns.add(gun);
            logger.fine("Added Gun to list: " + gun.getId());
            gun = null;
        }
    }

    private void endDocument(XMLEvent event, XMLEventReader reader, List<Gun> guns) {
        // Optional: log document end if needed
        logger.fine("End of XML document.");
    }
}
