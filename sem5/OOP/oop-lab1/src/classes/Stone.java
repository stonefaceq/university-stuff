package classes;

public class Stone {
    private int stoneID;
    private Valuability valuability;
    private String name;
    private float carats = 0;
    private float cost = 0;
    private float transparency = 0;

    public Stone() {}

    public Stone(Valuability valuability, String name, float carats, float cost, float transparency) {
        this.valuability = valuability;
        this.name = name;
        this.cost = cost;
        this.carats = carats;
        this.transparency = transparency;
    }

    public int getStoneID() {
        return stoneID;
    }

    public void setStoneID(int stoneID) {
        this.stoneID = stoneID;
    }

    public Valuability getValuability() {
        return valuability;
    }

    public void setValuability(Valuability valuability) {
        this.valuability = valuability;
    }

    public void setValuabilityFromText(String valText) {
        switch(valText) {
            case("PRECIOUS"):
                this.valuability = Valuability.PRECIOUS;
                break;
            case ("SEMIPRECIOUS"):
                this.valuability = Valuability.SEMIPRECIOUS;
                break;
            default:
                this.valuability = null;
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCarats(float carats) {
        if (carats < 0) {
            System.out.print("Carats amount is wrong - try again");
        } else {
            this.carats = carats;
        }
    }
    public void setCost(float cost) {
        if (cost < 0) {
            System.out.print("Cost is wrong - try again");
        } else {
            this.cost = cost;
        }
    }

    public void setTransparency(float transparency) {
        if (transparency < 0) {
            System.out.print("Carats amount is wrong - try again");
        } else {
            this.transparency = transparency;
        }
    }

    public void outputCost() {
        System.out.printf("%d:", (int) getCost());
    }

    public void outputCarats() {
        System.out.printf("%d:", (int) getCarats());
    }
    public float getCost() {
        return cost;
    }

    public float getCarats() {
        return carats;
    }

    public float getTransparency() {
        return transparency;
    }

}
