package org.example;

import java.util.Scanner;
import java.util.*;

public class Main {
    private static Manager managerInstance; // singleton instance of the Manager class
    private static final Map<String, CommandHandler> commandHandlers = new HashMap<>(); // map to store commands and their handlers

    public static void main(String[] args) {
        Scanner inputScanner = new Scanner(System.in);

        initializeCommands(); // initialize the available commands and their handlers

        System.out.println("Welcome to the Computation Manager!");
        displayMenu();

        while (true) {
            System.out.print("Enter a command: ");
            String userCommand = inputScanner.nextLine().trim().toLowerCase();

            // retrieve the handler for the first word of the command
            CommandHandler handler = commandHandlers.get(userCommand.split(" ")[0]);

            if (handler != null) {
                handler.handle(userCommand);
            } else {
                System.out.println("Invalid command. Please try again.");
            }
        }
    }

    private static void initializeCommands() {
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

    // interface for handling commands
    interface CommandHandler {
        void handle(String command);
    }

    // command handler for the "group" command
    static class GroupCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            String[] parts = command.split(" ");
            if (parts.length < 2) {
                System.out.println("Error: Invalid syntax for group command.");
                return;
            }

            try {
                // parse the value and create a new Manager instance
                int value = Integer.parseInt(parts[1]);
                managerInstance = new Manager(value);
                System.out.println("Created a new computation group with value: " + value);

                // set the time limit if provided
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

    // command handler for the "new" command to add computation components
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
                // Add a new computation component
                String componentType = parts[1];
                managerInstance.createComponent(componentType);
                System.out.println("Added a new computation component with symbol: " + componentType);
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    // command handler for the "run" command to start computations
    static class RunCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            if (managerInstance == null) {
                System.out.println("No computation group created. Use 'group <x>' to create a group first.");
                return;
            }
            managerInstance.execute(); // execute all tasks in the Manager instance
            System.out.println("Computation manager started...");
        }
    }

    // command handler for the "showsum" command to display results
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

    // command handler for the "exit" command to terminate the program
    static class ExitCommandHandler implements CommandHandler {
        @Override
        public void handle(String command) {
            System.out.println("Exiting the program...");
            System.exit(0);
        }
    }
}
