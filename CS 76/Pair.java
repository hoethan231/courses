/* Ethan Ho
 * Efficient Algorithims: Closest pair
 * Finding the closest pair of points using a divide-and-conquer approach
 */
import java.util.*;

public class Pair {
    private Point p1;
    private Point p2;

    public Pair(Point p1, Point p2) {
        this.p1 = p1;
        this.p2 = p2;
    }

    public static void main(String[] args) {
        Point[] points = new Point[100];
        for (int i = 0; i < points.length; i++) {
            points[i] = new Point(Math.random() * 100, Math.random() * 100);
        }
        Point[] OrderedByY = points.clone();
        Arrays.sort(OrderedByY, new CompareY());
    
        Pair closestPair = getClosest(points, OrderedByY, 0, points.length - 1);
        System.out.println("The shortest distance between two points would be: " + closestPair.getDistance());
    }
    
    
    public double getDistance() {
        return distance(p1, p2);
    }

    public static double distance(Point p1, Point p2) {
        return distance(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }

    public static double distance(double x1, double y1, double x2, double y2) {
        return Math.sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
    }

    public static Pair getClosest(Point[] ByX, Point[] ByY, int low, int high) {
        if (low >= high) {
            return null;
        } else if (low + 1 == high) {
            return new Pair(ByX[low], ByX[high]);
        }
    
        int midPoint = (low + high) / 2;
        Pair s1 = getClosest(ByX, ByY, low, midPoint);
        Pair s2 = getClosest(ByX, ByY, midPoint + 1, high);
    
        double distance = 0.0;
        Pair point = null;
    
        if (s1 == null && s2 == null) {
            distance = 0.0;
            point = null;
        } else if (s1 == null) {
            distance = s2.getDistance();
            point = s2;
        } else if (s2 == null) {
            distance = s1.getDistance();
            point = s1;
        } else {
            distance = Math.min(s1.getDistance(), s2.getDistance());
            if (s1.getDistance() <= s2.getDistance()) {
                point = s1;
            } else {
                point = s2;
            }
        }
    
        ArrayList<Point> leftSide = new ArrayList<>();
        ArrayList<Point> rightSide = new ArrayList<>();
    
        for (int i = 0; i < ByY.length; i++) {
            if (i <= midPoint && ByY[i].getX() - ByX[midPoint].getX() <= distance) {
                leftSide.add(ByY[i]);
            } else if (i > midPoint && ByY[i].getX() - ByX[midPoint].getX() <= distance) {
                rightSide.add(ByY[i]);
            }
        }
    
        int r = 0;
        for (int i = 0; i < leftSide.size(); i++) {
            while (r < rightSide.size() && rightSide.get(r).getY() <= leftSide.get(i).getY() - distance) {
                r++;
            }
            int r1 = r;
            while (r1 < rightSide.size() && Math.abs(rightSide.get(r1).getY() - leftSide.get(i).getY()) <= distance) {
                if (distance(leftSide.get(i), rightSide.get(r1)) < distance) {
                    distance = distance(leftSide.get(i), rightSide.get(r1));
                    point.p1 = leftSide.get(i);
                    point.p2 = rightSide.get(r1);
                }
                r1++;
            }
        }
    
        return point;
    }    
    
}

class Point implements Comparable<Point> {
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
        if (x < p.getX()) {
            return -1;
        } else if (x > p.getX()) {
            return 1;
        } else {
            if (y < p.getY()) {
                return -1;
            } else if (y > p.getY()) {
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

class CompareY implements java.util.Comparator<Point> {
    @Override
    public int compare(Point one, Point two) {
        if (one.getY() > two.getY()) {
            return -1;
        } else if (one.getY() < two.getY()) {
            return 1;
        } else {
            if (one.getX() > two.getX()) {
                return -1;
            }
            if (one.getX() < two.getX()) {
                return 1;
            }
            return 0;
        }
    }
}
