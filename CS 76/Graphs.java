/* Ethan Ho 
 * Graph
 * A program that reads the data for a graph from  a file and determines whether the graph is connected
 */

import java.io.*;
import java.util.*;
import java.net.*;

public class Graphs {
    int vertices;
    static LinkedList<Integer>[] adjacencyList;

    public Graphs(int vertices) {
        this.vertices = vertices;
        adjacencyList = new LinkedList[vertices];
        for (int i = 0; i < vertices; i++) {
            adjacencyList[i] = new LinkedList<>();
        }
    }

    public static void Edge(int source, int dest) {
        adjacencyList[source].addFirst(dest);
    }

    public static void isConnected(Graphs graph) {
        int vertices = graph.vertices;
        LinkedList<Integer>[] adjacencyList = Graphs.adjacencyList;

        boolean[] visited = new boolean[vertices];

        DFS(0, adjacencyList, visited);

        boolean connected = true;

        for (int i = 0; i < visited.length; i++) {
            if (!visited[i]) {
                connected = false;
                break;
            }
        }

        System.out.println(connected ? "Graph is connected" : "Graph is not connected");
    }

    public static void DFS(int source, LinkedList<Integer>[] adjacencyList, boolean[] visited) {
        visited[source] = true;

        for (int i = 0; i < adjacencyList[source].size(); i++) {
            int neighbor = adjacencyList[source].get(i);

            if (!visited[neighbor]) {
                DFS(neighbor, adjacencyList, visited);
            }
        }
    }

    public static void main(String[] args) {

        System.out.println("Enter the URL: ");
        System.out.println("");
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
    
        try {
            URI uri = new URI(input);
            URL url = uri.toURL();
            URLConnection connection = url.openConnection();
            BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line;
    
            if ((line = br.readLine()) != null) {
                System.out.println("The number of vertices is " + line);
                Graphs g = new Graphs(Integer.parseInt(line));
    
                while ((line = br.readLine()) != null) {
                    String[] vertices = line.split("\\s+");
                    System.out.print("Vertex " + vertices[0] + ": ");
                    for (int i = 1; i < vertices.length; i++) {
                        g.Edge(Integer.parseInt(vertices[0]), Integer.parseInt(vertices[i]));
                        System.out.print(" ( " + vertices[0] + ", " + vertices[i] + ")");
                    }
                    System.out.println();
                }
    
                br.close();
    
                // Check if the graph is connected
                Graphs.isConnected(g);
            } else {
                System.out.println("Empty file or invalid format");
            }
        } catch (URISyntaxException e) {
            System.out.println("Invalid URL syntax: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO error: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("An unexpected error occurred: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
