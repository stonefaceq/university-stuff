package org.example.models;

import lombok.Getter;
import org.example.models.types.Range;

import java.util.Objects;

@Getter
public class TTC {
    public static final String FIRING_RANGE =    "FiringRange";
    public static final String SIGHTING_RANGE =  "SightingRange";
    public static final String MAGAZINE =        "Magazine";
    public static final String SIGHT =           "Sight";

    private Range firingRange;
    private int sightingRange;
    private boolean magazine;
    private boolean Sight;


    public void setFiringRange(Range firingRange) {
        this.firingRange = firingRange;
    }

    public void setFiringRange(String firingRange) {
        this.firingRange = switch (firingRange) {
            case "Short" -> Range.Short;
            case "Mid" -> Range.Mid;
            case "Far" -> Range.Far;
            default -> throw new IllegalStateException("Unexpected value: " + firingRange);
        };
    }

    public void setSightingRange(int sightingRange) {
        this.sightingRange = sightingRange;
    }

    public void setSightingRange(String sightingRange) {
        this.sightingRange = Integer.parseInt(sightingRange);
    }

    public void setMagazine(boolean magazine) {
        this.magazine = magazine;
    }

    public void setMagazine(String magazine) {
        this.magazine = Boolean.parseBoolean(magazine);
    }

    public void setSight(boolean sight) {
        Sight = sight;
    }

    public void setSight(String sight) {
        Sight = Boolean.parseBoolean(sight);
    }

    @Override
    public String toString() {
        return "TTC{" +
                "firingRange=" + firingRange +
                ", sightingRange=" + sightingRange +
                ", magazine=" + magazine +
                ", Sight=" + Sight +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TTC ttc = (TTC) o;
        return sightingRange == ttc.sightingRange && magazine == ttc.magazine && Sight == ttc.Sight && firingRange == ttc.firingRange;
    }

    @Override
    public int hashCode() {
        return Objects.hash(firingRange, sightingRange, magazine, Sight);
    }
}
