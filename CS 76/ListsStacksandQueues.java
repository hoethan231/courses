/* Ethan Ho
 * Lists, Stacks, and Queues: Point
 * A class that creates a hundred random points and displays the sorted array 
 */ 

 import java.util.*;

public class ListsStacksandQueues {
    
    public static void main(String[] args) {

        //creates an array of random point
        Point[] points = new Point[100];
        for(int i = 0; i < points.length; i++) {
            points[i] = new Point(Math.random()*100,Math.random()*100);
        }
        

        //Prints ascending list ordered by x
        System.out.println("Sorted by X positon:");
        Arrays.sort(points);
        for(Point point : points) {
            System.out.println(point.toString());
        }
        System.out.println("");


        //Prints descending list ordered by y
        System.out.println("Sorted by Y positon:");
        Arrays.sort(points, new CompareY());
        for(Point point : points) {
            System.out.println(point.toString());
        }
        System.out.println("");
    }



}

class Point implements Comparable<Point>{

    private double x;
    private double y;

    public Point(double x, double y) {

        this.x = x;
        this.y = y;

    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    @Override
    public int compareTo(Point p) {
        if(x < p.getX()) {
            return -1;
        }
        else if(x > p.getX()) {
            return 1;
        }
        else {
            if(y < p.getY()) {
                return -1;
            }
            else if(y > p.getY()) {
                return 1;
            }
            return 0;
        }
    }

    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }

}


//Compares the Y position of the point
class CompareY implements java.util.Comparator<Point> {

    @Override
    public int compare(Point one, Point two) {
        if(one.getY() > two.getY()) {
            return -1;
        }
    
        else if(one.getY() < two.getY()) {
            return 1;
        }

        else {
            if(one.getX() > two.getX()) {
                return -1;
            }
        
            if(one.getX() < two.getX()) {
                return 1;
            }
            return 0;
        }
        
    }

}
