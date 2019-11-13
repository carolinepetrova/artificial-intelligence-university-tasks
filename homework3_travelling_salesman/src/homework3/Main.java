package homework3;

public class Main {

    public static void main(String[] args) {
        // Add 20 random cities
        for (int i = 0; i < 20; i++) {
            TourManager.addCity(new City());
        }

        // Initialize population
        Population pop = new Population(50, true);
        int initialDistance = pop.getFittest().getDistance();

        // Evolve population for 100 generations
        pop = GA.evolvePopulation(pop);
        for (int i = 0; i < 100; i++) {
            pop = GA.evolvePopulation(pop);

            // Print some of the paths to see how they evolve
            if (i==10 || i == 40 || i == 70 || i == 90) {
                System.out.println(i + "th path: " + pop.getFittest());
            }
        }

        // Print final results
        System.out.println("Solution:" + pop.getFittest());
        System.out.println("\nInfo:");
        System.out.println("Initial distance: " + initialDistance);
        System.out.println("Solution distance: " + pop.getFittest().getDistance());
    }
}

