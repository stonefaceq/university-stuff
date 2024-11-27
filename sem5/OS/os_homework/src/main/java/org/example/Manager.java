package org.example;

import java.util.*;
import java.util.concurrent.*;

public class Manager {
    private final ExecutorService executorService; // thread pool for task execution
    private final CountDownLatch latch; // synchronization mechanism to start all tasks simultaneously
    private int value = -1;
    private long timeConstraint = Long.MAX_VALUE; // maximum allowed time for task execution
    private final List<String> pendingTasks = new ArrayList<>(); // queue of tasks to execute
    private final Map<Thread, Future<Number>> computationFutures = new HashMap<>(); // stores computation results for each thread
    private final Map<Thread, Long> timeRecords = new HashMap<>(); // records execution time for each thread

    public Manager(int value) {
        this.value = value;
        this.executorService = Executors.newFixedThreadPool(2); // initialize thread pool with 2 threads
        this.latch = new CountDownLatch(1); // latch to control the start of task execution
    }

    public void defineExecutionLimit(long limit) {
        this.timeConstraint = limit;
    }

    public void createComponent(String symbol) {
        if (!symbol.equals("sq") && !symbol.equals("sr")) {
            throw new IllegalArgumentException("Invalid symbol provided.");
        }
        pendingTasks.add(symbol); // add the task to the queue
        System.out.println("Component added: " + symbol);
    }

    private void submitTask(String type) {
        Callable<Number> task = () -> {
            long startTime = System.currentTimeMillis(); // record start time
            Number result = null;

            try {
                latch.await(); // wait for the signal to start execution
                if (type.equals("square")) {
                    System.out.println("Computing square on " + Thread.currentThread().getName());
                    Thread.sleep(2000); // simulate workload
                    result = value * value;
                } else if (type.equals("sqrt")) {
                    System.out.println("Computing sqrt on " + Thread.currentThread().getName());
                    Thread.sleep(3000); // simulate workload
                    result = Math.sqrt(value);
                }
            } catch (InterruptedException e) {
                System.out.println(Thread.currentThread().getName() + " was interrupted.");
            }

            long elapsedTime = System.currentTimeMillis() - startTime;
            timeRecords.put(Thread.currentThread(), elapsedTime);

            // check if the task completed within the time constraint
            if (elapsedTime <= timeConstraint) {
                computationFutures.put(Thread.currentThread(), CompletableFuture.completedFuture(result));
                System.out.println(Thread.currentThread().getName() + " completed in " + elapsedTime + " ms");
            } else {
                computationFutures.put(Thread.currentThread(), CompletableFuture.completedFuture(null));
                System.out.println(Thread.currentThread().getName() + " exceeded time limit of " + timeConstraint + " ms");
            }

            return result;
        };

        executorService.submit(task); // submit the task to the thread pool
    }

    public void execute() {
        latch.countDown(); // signal all threads to start execution
        for (String task : pendingTasks) {
            if (task.equals("sq")) {
                submitTask("square");
            } else if (task.equals("sr")) {
                submitTask("sqrt");
            }
        }
        pendingTasks.clear(); // clear the task queue after execution
        System.out.println("All tasks have been executed.");
    }


    public void generateSummary() {
        try {
            executorService.shutdown(); // initiate thread pool shutdown
            while (!executorService.isTerminated()) {
                Thread.sleep(100); // wait for all threads to complete
            }

            // iterate through computation results and print a summary
            computationFutures.forEach((thread, future) -> {
                try {
                    Number result = future.get();
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
