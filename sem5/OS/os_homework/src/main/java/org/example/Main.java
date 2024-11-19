package org.example;

import java.util.Scanner;
import java.util.*;

public class Main {
    private static Manager managerInstance;
    private static final Map<String, CommandHandler> commandHandlers = new HashMap<>();

    public static void main(String[] args) {
        Scanner inputScanner = new Scanner(System.in);

        initializeCommands(); // Ініціалізація команд

        System.out.println("Welcome to the Computation Manager!");
        displayMenu(); // Виведення меню команд

        while (true) {
            System.out.print("Enter a command: ");
            String userCommand = inputScanner.nextLine().trim().toLowerCase(); // Приводимо команду до нижнього регістру

            CommandHandler handler = commandHandlers.get(userCommand.split(" ")[0]); // Отримуємо обробник для першого слова

            if (handler != null) {
                handler.handle(userCommand); // Виконання обробки відповідної команди
            } else {
                System.out.println("Invalid command. Please try again.");
            }
        }
    }

    private static void initializeCommands() {
        // Ініціалізація мапи з командами та їх відповідними обробниками
        commandHandlers.put("group", new GroupCommandHandler());
        commandHandlers.put("new", new NewComponentCommandHandler());
        commandHandlers.put("run", new RunCommandHandler());
        commandHandlers.put("showsum", new SummaryCommandHandler());
        commandHandlers.put("exit", new ExitCommandHandler());
    }

    private static void displayMenu() {
        System.out.println("Available commands:");
        System.out.println("  group <x> [limit <time>] - Create a new computation group with value x and optional time limit.");
        System.out.println("  new <symbol> - Add a new computation component (s for square, r for square root).");
        System.out.println("  run - Start all computation threads.");
        System.out.println("  showsum - Display the computation results and timing summary.");
        System.out.println("  exit - Exit the program.");
    }

    // Абстракція для обробки команд
    interface CommandHandler {
        void handle(String command);
    }

    // Командний обробник для групи
    static class GroupCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            String[] parts = command.split(" ");
            if (parts.length < 2) {
                System.out.println("Error: Invalid syntax for group command.");
                return;
            }

            try {
                int value = Integer.parseInt(parts[1]);
                managerInstance = new Manager(value);
                System.out.println("Created a new computation group with value: " + value);

                if (parts.length > 3 && "limit".equals(parts[2])) {
                    long timeLimit = Long.parseLong(parts[3]);
                    managerInstance.defineExecutionLimit(timeLimit);
                    System.out.println("Set execution time limit to: " + timeLimit + " ms.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Error: Invalid number format in group command.");
            }
        }
    }

    // Командний обробник для нового компонента
    static class NewComponentCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            if (managerInstance == null) {
                System.out.println("No computation group created. Use 'group <x>' to create a group first.");
                return;
            }

            String[] parts = command.split(" ");
            if (parts.length != 2) {
                System.out.println("Error: Invalid syntax for new command.");
                return;
            }

            try {
                String componentType = parts[1];
                managerInstance.createComponent(componentType);
                System.out.println("Added a new computation component with symbol: " + componentType);
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    // Командний обробник для запуску обчислень
    static class RunCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            if (managerInstance == null) {
                System.out.println("No computation group created. Use 'group <x>' to create a group first.");
                return;
            }
            managerInstance.execute();
            System.out.println("Computation manager started...");
        }
    }

    // Командний обробник для показу результатів
    static class SummaryCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            if (managerInstance == null) {
                System.out.println("No computation group created. Use 'group <x>' to create a group first.");
                return;
            }
            managerInstance.generateSummary();
        }
    }

    // Командний обробник для завершення програми
    static class ExitCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            System.out.println("Exiting the program...");
            System.exit(0); // Завершує програму
        }
    }
}
