package org.example.models;

import lombok.Getter;
import lombok.Setter;
import org.example.models.types.Handiness;

import java.util.Comparator;
import java.util.Objects;
import java.util.logging.Logger;

@Getter
public class Gun {
    private static final Logger logger = Logger.getLogger(Gun.class.getName());

    public static final String GUN =      "Gun";
    public static final String ID =       "id";
    public static final String MODEL =    "Model";
    public static final String HANDY =    "Handy";
    public static final String ORIGIN =   "Origin";
    public static final String MATERIAL = "Material";

    private int id;
    @Setter private String model;
    private Handiness handy;
    @Setter private String origin;
    @Setter private TTC ttc;
    @Setter private String material;

    public static class GunComparator implements Comparator<Gun> {
        @Override
        public int compare(Gun o1, Gun o2) {
            logger.info("Comparing Gun IDs: " + o1.id + " and " + o2.id);
            return Integer.compare(o1.id, o2.id);
        }
    }

    public void setId(int id) {
        this.id = id;
        logger.info("Setting ID: " + id);
    }

    public void setId(String id) {
        this.id = Integer.parseInt(id);
        logger.info("Setting ID from String: " + id);
    }

    public void setHandy(Handiness handiness) {
        this.handy = handiness;
        logger.info("Setting Handy: " + handiness);
    }

    public void setHandy(String handiness) {
        handy = switch (handiness) {
            case "One" -> Handiness.One;
            case "Two" -> Handiness.Two;
            default -> throw new IllegalStateException("Unexpected value: " + handiness);
        };
        logger.info("Setting Handy from String: " + handiness);
    }

    @Override
    public String toString() {
        return "Gun{" +
                "id=" + id +
                ", model='" + model + '\'' +
                ", handy=" + handy +
                ", origin='" + origin + '\'' +
                ", ttc=" + ttc +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Gun gun = (Gun) o;
        boolean result = id == gun.id && Objects.equals(model, gun.model) && handy == gun.handy && Objects.equals(origin, gun.origin) && Objects.equals(ttc, gun.ttc) && Objects.equals(material, gun.material);
        logger.info("Equals check result: " + result);
        return result;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, model, handy, origin, ttc, material);
    }
}
