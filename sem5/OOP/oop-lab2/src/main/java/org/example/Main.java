package org.example;

import org.example.models.Gun;
import org.example.parsers.StAXXMLParser;
import org.example.parsers.XMLParser;

import java.util.List;
import java.util.logging.Logger;

public class Main {
    private static final Logger logger = Logger.getLogger(Main.class.getName());

    public static void main(String[] args) {
        XMLParser parser = new StAXXMLParser();
        List<Gun> guns = parser.parse("src/main/resources/gun.xml", "src/main/resources/gun.xsd");

        if (guns != null) {
            guns.sort(new Gun.GunComparator());
            logger.info(guns.stream().map(gun -> gun.toString() + "\n").reduce((a, b) -> a + b).get());
        } else {
            logger.warning("Was not able to load xml file");
        }
    }
}
