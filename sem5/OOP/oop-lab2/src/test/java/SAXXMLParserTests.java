
import org.example.models.Gun;
import org.example.models.TTC;
import org.example.models.types.Handiness;
import org.example.models.types.Range;
import org.example.parsers.SAXXMLParser;
import org.junit.jupiter.api.Test;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;

import static org.junit.jupiter.api.Assertions.*;

public class SAXXMLParserTests {
    private static final String CORRECT_XML_PATH = "src/test/resources/correct-gun.xml";
    private static final String INCORRECT_XML_PATH = "src/test/resources/incorrect-gun.xml";
    private static final String XSD_PATH = "src/test/resources/gun.xsd";

    @Test
    void parse_WithoutXSDCheck_CorrectGun_ParsesSuccessfully() throws ParserConfigurationException, SAXException {
        SAXXMLParser parser = new SAXXMLParser();
        Gun actual = parser.parse(CORRECT_XML_PATH).get(0);

        Gun expected = new Gun();
        expected.setId(10);
        expected.setModel("ShotGun");
        expected.setHandy(Handiness.One);
        expected.setOrigin("United States of America");

        TTC ttc = new TTC();
        ttc.setFiringRange(Range.Short);
        ttc.setSightingRange(10);
        ttc.setMagazine(true);
        ttc.setSight(true);

        expected.setTtc(ttc);
        expected.setMaterial("Metal");

        assertEquals(expected, actual);
    }

    @Test
    void parse_WithoutXSDCheck_IncorrectGun_ReturnsNullForMissingField() throws ParserConfigurationException, SAXException {
        SAXXMLParser parser = new SAXXMLParser();
        Gun result = parser.parse(INCORRECT_XML_PATH).get(0);
        assertNull(result.getMaterial());
    }

    @Test
    void parse_WithXSDCheck_CorrectGun_ParsesSuccessfully() throws ParserConfigurationException, SAXException {
        SAXXMLParser parser = new SAXXMLParser();
        Gun actual = parser.parse(CORRECT_XML_PATH, XSD_PATH).get(0);

        Gun expected = new Gun();
        expected.setId(10);
        expected.setModel("ShotGun");
        expected.setHandy(Handiness.One);
        expected.setOrigin("United States of America");

        TTC ttc = new TTC();
        ttc.setFiringRange(Range.Short);
        ttc.setSightingRange(10);
        ttc.setMagazine(true);
        ttc.setSight(true);

        expected.setTtc(ttc);
        expected.setMaterial("Metal");

        assertEquals(expected, actual);
    }

    @Test
    void parse_WithXSDCheck_IncorrectGun_ReturnsNull() throws ParserConfigurationException, SAXException {
        SAXXMLParser parser = new SAXXMLParser();
        assertNull(parser.parse(INCORRECT_XML_PATH, XSD_PATH));
    }
}