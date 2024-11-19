package org.example;

import java.util.*;
import java.util.concurrent.*;

public class Manager {
    private final ExecutorService executorService;
    private final CountDownLatch latch;
    private int value = -1;
    private long timeConstraint = Long.MAX_VALUE;
    private final List<String> pendingTasks = new ArrayList<>(); // Список задач
    private final Map<Thread, Future<Number>> computationFutures = new HashMap<>();
    private final Map<Thread, Long> timeRecords = new HashMap<>();

    public Manager(int value) {
        this.value = value;
        this.executorService = Executors.newFixedThreadPool(2); // Пул з 2 потоків
        this.latch = new CountDownLatch(1); // Лічильник для сигналізації готовності
    }

    public void defineExecutionLimit(long limit) {
        this.timeConstraint = limit;
    }

    public void createComponent(String symbol) {
        if (!symbol.equals("sq") && !symbol.equals("sr")) {
            throw new IllegalArgumentException("Invalid symbol provided.");
        }
        pendingTasks.add(symbol); // Додаємо компонент у чергу задач
        System.out.println("Component added: " + symbol);
    }

    private void submitTask(String type) {
        Callable<Number> task = () -> {
            long startTime = System.currentTimeMillis();
            Number result = null;

            try {
                latch.await(); // Чекаємо команди "run"
                if (type.equals("square")) {
                    System.out.println("Computing square on " + Thread.currentThread().getName());
                    Thread.sleep(2000); // Симулюємо роботу
                    result = value * value; // Обчислюємо квадрат
                } else if (type.equals("sqrt")) {
                    System.out.println("Computing sqrt on " + Thread.currentThread().getName());
                    Thread.sleep(3000); // Симулюємо роботу
                    result = Math.sqrt(value); // Обчислюємо квадратний корінь
                }
            } catch (InterruptedException e) {
                System.out.println(Thread.currentThread().getName() + " was interrupted.");
            }

            long elapsedTime = System.currentTimeMillis() - startTime;
            timeRecords.put(Thread.currentThread(), elapsedTime);

            if (elapsedTime <= timeConstraint) {
                computationFutures.put(Thread.currentThread(), CompletableFuture.completedFuture(result));
                System.out.println(Thread.currentThread().getName() + " completed in " + elapsedTime + " ms");
            } else {
                computationFutures.put(Thread.currentThread(), CompletableFuture.completedFuture(null));
                System.out.println(Thread.currentThread().getName() + " exceeded time limit of " + timeConstraint + " ms");
            }

            return result;
        };

        executorService.submit(task);
    }

    public void execute() {
        latch.countDown(); // Сигналізуємо, що можна запускати потоки
        for (String task : pendingTasks) {
            if (task.equals("sq")) {
                submitTask("square");
            } else if (task.equals("sr")) {
                submitTask("sqrt");
            }
        }
        pendingTasks.clear(); // Очищаємо чергу після запуску задач
        System.out.println("All tasks have been executed.");
    }

    public void generateSummary() {
        try {
            executorService.shutdown();
            while (!executorService.isTerminated()) {
                // Чекаємо, поки всі потоки завершать виконання
                Thread.sleep(100);
            }

            computationFutures.forEach((thread, future) -> {
                try {
                    Number result = future.get(); // Отримуємо результат обчислення
                    long elapsedTime = timeRecords.getOrDefault(thread, -1L);
                    if (result != null) {
                        System.out.println(thread.getName() + " computed: " + result + " in " + elapsedTime + " ms");
                    } else {
                        System.out.println(thread.getName() + " failed to compute within the time limit.");
                    }
                } catch (InterruptedException | ExecutionException e) {
                    System.out.println(thread.getName() + " encountered an error during execution.");
                }
            });
        } catch (InterruptedException e) {
            System.out.println("Error while waiting for threads to finish.");
        }
    }
}
