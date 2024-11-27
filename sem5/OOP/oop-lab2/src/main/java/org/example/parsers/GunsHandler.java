package org.example.parsers;

import org.example.models.Gun;
import org.example.models.TTC;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

class GunsHandler extends DefaultHandler {
    private static final Logger logger = Logger.getLogger(GunsHandler.class.getName());

    private List<Gun> guns;
    private StringBuilder elementValue;

    private Gun gun;

    List<Gun> getGuns() {
        return guns;
    }

    @Override
    public void characters(char[] ch, int start, int length) {
        if (elementValue == null) {
            elementValue = new StringBuilder();
        } else {
            elementValue.append(ch, start, length);
        }
    }

    @Override
    public void startDocument() {
        guns = new ArrayList<>();
        logger.info("Started parsing the XML document.");
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) {
        if (qName.equals(Gun.GUN)) {
            gun = new Gun();
            gun.setTtc(new TTC());
            gun.setId(Integer.parseInt(attributes.getValue(Gun.ID)));
            logger.fine("Started parsing a new gun with ID: " + gun.getId());
        } else {
            this.elementValue = new StringBuilder();
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) {
        switch (qName) {
            case Gun.MODEL:
                String model = elementValue.toString();
                gun.setModel(model);
                logger.fine("Set model for gun with ID " + gun.getId() + ": " + model);
                break;
            case Gun.HANDY:
                String handy = elementValue.toString();
                gun.setHandy(handy);
                logger.fine("Set handy for gun with ID " + gun.getId() + ": " + handy);
                break;
            case Gun.ORIGIN:
                String origin = elementValue.toString();
                gun.setOrigin(origin);
                logger.fine("Set origin for gun with ID " + gun.getId() + ": " + origin);
                break;
            case TTC.FIRING_RANGE:
                String firingRange = elementValue.toString();
                gun.getTtc().setFiringRange(firingRange);
                logger.fine("Set firing range for gun with ID " + gun.getId() + ": " + firingRange);
                break;
            case TTC.SIGHTING_RANGE:
                String sightingRange = elementValue.toString();
                gun.getTtc().setSightingRange(sightingRange);
                logger.fine("Set sighting range for gun with ID " + gun.getId() + ": " + sightingRange);
                break;
            case TTC.MAGAZINE:
                String magazine = elementValue.toString();
                gun.getTtc().setMagazine(magazine);
                logger.fine("Set magazine for gun with ID " + gun.getId() + ": " + magazine);
                break;
            case TTC.SIGHT:
                String sight = elementValue.toString();
                gun.getTtc().setSight(sight);
                logger.fine("Set sight for gun with ID " + gun.getId() + ": " + sight);
                break;
            case Gun.MATERIAL:
                String material = elementValue.toString();
                gun.setMaterial(material);
                logger.fine("Set material for gun with ID " + gun.getId() + ": " + material);
                break;
            case Gun.GUN:
                guns.add(gun);
                logger.fine("Added gun with ID " + gun.getId() + " to the list.");
                break;
        }
    }

    @Override
    public void endDocument() {
        gun = null;
        elementValue = null;
        logger.info("Finished parsing the XML document.");
    }
}
