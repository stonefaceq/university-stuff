package classes;

import java.util.Comparator;
import java.util.List;

public class Necklace {
    private int necklaceID;
    private String name;
    private List<Stone> stones;

    public Necklace() {}

    public Necklace(String name,
                    List<Stone> stones) {
        this.name = name;
        this.stones = stones;
    }

    public List<Stone> getStones() {
        return stones;
    }

    public int getNecklaceID() {
        return necklaceID;
    }

    public void setNecklaceID(int necklaceID) {
        this.necklaceID = necklaceID;
    }

    public void setStones(List<Stone> stones) {
        this.stones = stones;
    }

    public void printTotalCost() {
        int totalCost = stones.stream()
                .mapToInt(stone -> (int) (stone.getCost()))
                .sum();


        System.out.printf("%d", totalCost);
    }

    public void printTotalCarats() {
        int totalCarats = stones.stream()
                .mapToInt(stone -> (int) (stone.getCarats()))
                .sum();


        System.out.printf("%d", totalCarats);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void sortStonesByValuability() {
        stones.sort(Comparator.comparing(stone -> stone.getValuability().toString()));
    }


    public void print() {
        stones.forEach(stone -> {
            String name = stone.getName();
            String valuability = stone.getValuability().toString();


            System.out.printf("Name: %s, Valuability: %s, Cost: %s, Carats: %s", name, valuability, stone.getCost(), stone.getCarats());
            stone.outputCost();
            stone.outputCarats();
            System.out.println();
        });
    }
}

