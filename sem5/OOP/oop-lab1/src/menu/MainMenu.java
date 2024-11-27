package menu;

import database.*;
import classes.*;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.Scanner;

public class MainMenu {

    private static DBManager dbManager;

    public static void startMenu() throws SQLException {
        ConnectDB connectDB = new ConnectDB(); // Assuming ConnectDB handles connections
        Connection connection = connectDB.getConnection();
        dbManager = new DBManager(connectDB);

        DB_Initializer dbInitializer = new DB_Initializer(connection);
        dbInitializer.createTables(); // Initialize tables if not exists

        Scanner scanner = new Scanner(System.in);
        int choice;

        do {
            System.out.println("============================== MENU ==============================");
            System.out.println("1. Add Stone                               2. View Stone");
            System.out.println("3. Update Stone                            4. Delete Stone");
            System.out.println("5. View All Stones                         6. Add Necklace");
            System.out.println("7. View Necklace                           8. Delete Necklace ");
            System.out.println("9. View All Necklaces                      10. Add Stone to Necklace");
            System.out.println("11. Remove Stone from Necklace             12. View Necklace's total cost ");
            System.out.println("13. View Necklace's total carats           14. Sort Necklace by Valuability");
            System.out.println("15. Find Stone by Transparency             16. Clear database                                  ");
            System.out.println("0. Exit");
            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    addStone(scanner);
                    break;
                case 2:
                    viewStone(scanner);
                    break;
                case 3:
                    updateStone(scanner);
                    break;
                case 4:
                    deleteStone(scanner);
                    break;
                case 5:
                    viewAllStones();
                    break;
                case 6:
                    addNecklace(scanner);
                    break;
                case 7:
                    viewNecklace(scanner);
                    break;
                case 8:
                    deleteNecklace(scanner);
                    break;
                case 9:
                    viewAllNecklaces();
                    break;
                case 10:
                    addStoneToNecklace(scanner);
                    break;
                case 11:
                    removeStoneFromNecklace(scanner);
                    break;
                case 12:
                    viewNecklaceTotalCost(scanner);
                    break;
                case 13:
                    viewNecklaceTotalCarats(scanner);
                    break;
                case 14:
                    sortNecklaceByValuability(scanner);
                    break;
                case 15:
                    findStoneByTransparency(scanner);
                    break;
                case 16:
                    clearDatabase(scanner);
                case 0:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 0);

        scanner.close();
    }




    private static void addStone(Scanner scanner) {
        scanner.nextLine();
        System.out.print("Enter stone name: ");
        String name = scanner.nextLine();
        System.out.print("Enter stone cost: ");
        float cost = Float.parseFloat(scanner.nextLine());
        Valuability valuability = null;
        while (valuability == null) {
            System.out.print("Enter valuability. 1 - precious, 2 - semiprecious.");
            String val = scanner.nextLine();
            switch (val) {
                case "1":
                    valuability = Valuability.PRECIOUS;
                    break;
                case "2":
                    valuability = Valuability.SEMIPRECIOUS;
                    break;
                default:
                    System.out.println("Wrong valuability option.");
            }
        }
        System.out.print("Enter stone carats: ");
        float carats = Float.parseFloat(scanner.nextLine());
        float transparency = -1f;
        while (transparency == -1f) {
            System.out.print("Enter stone transparency (between 0 and 100: ");
            transparency = Float.parseFloat(scanner.nextLine());
            if (transparency > 100 || transparency < 0) {
                System.out.println("Invalid transparency, must be betweeen 0 and 100.");
                transparency = -1f;
                System.out.println();
            }
        }



        Stone stone = new Stone(valuability, name, carats, cost, transparency);
        dbManager.insertStone(stone);
        System.out.println("Stone added successfully!");
    }



    private static void viewStone(Scanner scanner) {
        Stone stone = null;
        while (stone == null) {
            System.out.print("Enter stone ID: ");
            int id = scanner.nextInt();
            stone = dbManager.getStoneById(id);
            if (stone != null) {
                System.out.println("Stone: " + stone.getName() + ", Valuability: " + stone.getValuability() + ", Cost:" + stone.getCost() + "Carats:" + stone.getCarats() + "Transparency:" + stone.getTransparency());
            } else {
                System.out.println("Error: Invalid stone ID.");
                return;
            }
        }
    }
    private static void updateStone(Scanner scanner) {
        Stone stone = null;
        while (stone == null) {
            System.out.print("Enter stone ID to update: ");
            int id = scanner.nextInt();
            scanner.nextLine();
            stone = dbManager.getStoneById(id);
            if (stone != null) {
                System.out.print("Enter new stone name: ");
                String name = scanner.nextLine();
                System.out.print("Enter new stone cost: ");
                float cost = Float.parseFloat(scanner.nextLine());

                Valuability valuability = null;
                while (valuability == null) {
                    System.out.print("Enter new stone's valability. 1 = precious, 2 = semiprecious. ");
                    String val = scanner.nextLine();
                    switch(val) {
                        case "1":
                            valuability = Valuability.PRECIOUS;
                            break;
                        case "2":
                            valuability = Valuability.SEMIPRECIOUS;
                            break;
                        default:
                            System.out.println("Wrong valuability option.");
                    }

                }
                System.out.print("Enter new stone carats: ");
                float carats = Float.parseFloat(scanner.nextLine());
                float transparency = -1f;
                while (transparency == -1f) {
                    System.out.print("Enter stone transparency (between 0 and 100): ");
                    transparency = Float.parseFloat(scanner.nextLine());
                    if (transparency > 100 || transparency < 0) {
                        System.out.println("Invalid transparency, must be betweeen 0 and 100.");
                        transparency = -1f;
                        System.out.println();
                    }
                }

                stone.setName(name);
                stone.setCost(cost);
                stone.setValuability(valuability);
                stone.setCarats(carats);
                stone.setTransparency(transparency);
                dbManager.updateStone(stone);
                System.out.println("Stone updated successfully.");
            } else {
                System.out.println("Error: Invalid stone ID.");
                return;
            }
        }
    }

    private static void deleteStone(Scanner scanner) {
        System.out.print("Enter stone ID to delete: ");
        int id = scanner.nextInt();
        Stone stone = dbManager.getStoneById(id);
        if (stone != null) {
            dbManager.deleteStoneById(id);
            System.out.println("Stone deleted successfully.");
        } else {
            System.out.println("Error: Invalid stone ID.");
        }
    }


    private static void viewAllStones() {
        dbManager.printAllStones();
    }

    private static void viewAllNecklaces() {
        dbManager.printAllNecklaces();
    }

    private static void addNecklace(Scanner scanner) {
        scanner.nextLine(); // Clear the buffer
        System.out.print("Enter necklace name: ");
        String name = scanner.nextLine();
        Necklace necklace = new Necklace(name, null);
        dbManager.insertNecklace(necklace);
    }

    private static void addStoneToNecklace(Scanner scanner) {
        System.out.print("Enter necklace ID: ");
        int necklaceId = scanner.nextInt();
        System.out.print("Enter stone ID to add: ");
        int stoneId = scanner.nextInt();
        dbManager.addStoneToNecklace(necklaceId, stoneId);
    }

    private static void removeStoneFromNecklace(Scanner scanner) {
        System.out.print("Enter necklace ID: ");
        int necklaceId = scanner.nextInt();
        System.out.print("Enter stone ID to remove: ");
        int stoneId = scanner.nextInt();
        dbManager.removeStoneFromNecklace(necklaceId, stoneId);
    }

    private static void viewNecklace(Scanner scanner) {
        System.out.print("Enter necklace ID: ");
        int necklaceId = scanner.nextInt();
        dbManager.viewNecklace(necklaceId);
    }

    private static void deleteNecklace(Scanner scanner) {
        System.out.print("Enter necklace ID to delete: ");
        int necklaceId = scanner.nextInt();
        dbManager.deleteNecklaceById(necklaceId);
    }

    private static void viewNecklaceTotalCarats(Scanner scanner) {
        System.out.print("Enter necklace ID to view total duration of stones: ");
        int necklaceId = scanner.nextInt();
        Necklace nec = dbManager.getNecklaceById(necklaceId);
        nec.printTotalCarats();
        System.out.println();
    }
    private static void viewNecklaceTotalCost(Scanner scanner) {
        System.out.print("Enter necklace ID to view total duration of stones: ");
        int necklaceId = scanner.nextInt();
        Necklace nec = dbManager.getNecklaceById(necklaceId);
        nec.printTotalCost();
        System.out.println();
    }

    private static void sortNecklaceByValuability(Scanner scanner) {
        System.out.print("Enter necklace ID to sort by genre: ");
        int necklaceId = scanner.nextInt();
        Necklace nec = dbManager.getNecklaceById(necklaceId);
        nec.sortStonesByValuability();
        System.out.println("Stones sorted!");
    }

    private static void findStoneByTransparency(Scanner scanner) {
        System.out.print("Enter lower limit of transparency: ");
        int tran_lower = scanner.nextInt();
        System.out.print("\nEnter higher limit of transparency: ");
        int tran_higher = scanner.nextInt();
        if(tran_higher < tran_lower) {
            System.out.println("Incorrect input!");
            return;
        }
        dbManager.findStonesByTransparency(tran_lower, tran_higher);
        System.out.println();
    }

    private static void clearDatabase(Scanner scanner) {
        dbManager.clearDatabase();
    }
}