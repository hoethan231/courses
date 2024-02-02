/* Ethan Ho
 * TestGeometricObjects
 * New Triangle class that Extends the Geometric Object class (All classes other than Triangle were from source code)
 */

import java.util.Scanner;

public class TestGeometricObjects {

    public static void main(String args[]) {

        Scanner input = new Scanner(System.in);
        
        System.out.println("Please enter the sides of a triangle: ");
        double s1 = input.nextDouble();
        double s2 = input.nextDouble();
        double s3 = input.nextDouble();

        System.out.println("What is the color of the triangle: ");
        String color = input.next();

        System.out.println("Is the triangle filled (true/false): ");
        boolean filled = input.nextBoolean();

        Triangle tri = new Triangle(s1, s2, s3, color, filled);
        
        System.out.println(tri);
        
        Rectangle rec = new Rectangle(5, 10);
        Circle circ = new Circle(10);
        
        System.out.println("");
        System.out.println(rec);
        System.out.println("");
        System.out.println(circ);
    }

}

abstract class GeometricObject {
  private String color = "white";
  private boolean filled;
  private java.util.Date dateCreated;

  protected GeometricObject() {
    dateCreated = new java.util.Date();
  }

  /** Construct a geometric object with color and filled value */
  protected GeometricObject(String color, boolean filled) {
    dateCreated = new java.util.Date();
    this.color = color;
    this.filled = filled;
  }

  public String getColor() {
    return color;
  }

  /** Set a new color */
  public void setColor(String color) {
    this.color = color;
  }

  /** Return filled. Since filled is boolean,
   *  the get method is named isFilled */
  public boolean isFilled() {
    return filled;
  }

  /** Set a new filled */
  public void setFilled(boolean filled) {
    this.filled = filled;
  }

  /** Get dateCreated */
  public java.util.Date getDateCreated() {
    return dateCreated;
  }

  @Override
  public String toString() {
    return "created on " + dateCreated + "\ncolor: " + color +
      " and filled: " + filled;
  }

  /** Abstract method getArea */
  public abstract double getArea();

  /** Abstract method getPerimeter */
  public abstract double getPerimeter();
}

class Circle extends GeometricObject {
    private double radius;
  
    public Circle() {
    }
  
    public Circle(double radius) {
      this.radius = radius;
    }
  
    /** Return radius */
    public double getRadius() {
      return radius;
    }
  
    /** Set a new radius */
    public void setRadius(double radius) {
      this.radius = radius;
    }
  
    @Override /** Return area */
    public double getArea() {
      return radius * radius * Math.PI;
    }
  
    /** Return diameter */
    public double getDiameter() {
      return 2 * radius;
    }
  
    @Override /** Return perimeter */
    public double getPerimeter() {
      return 2 * radius * Math.PI;
    }
  
    /* Print the circle info */
    public void printCircle() {
      System.out.println("The circle is created " + getDateCreated() +
        " and the radius is " + radius);
    }

    public String toString() {
        return "\nCircle: \n" + super.toString() + "\nArea: " + getArea() + "\nPerimeter: " + getPerimeter(); 
    }
  }

class Rectangle extends GeometricObject {
    private double width;
    private double height;
  
    public Rectangle() {
    }
  
    public Rectangle(double width, double height) {
      this.width = width;
      this.height = height;
    }
  
    /** Return width */
    public double getWidth() {
      return width;
    }
  
    /** Set a new width */
    public void setWidth(double width) {
      this.width = width;
    }
  
    /** Return height */
    public double getHeight() {
      return height;
    }
  
    /** Set a new height */
    public void setHeight(double height) {
      this.height = height;
    }
  
    @Override /** Return area */
    public double getArea() {
      return width * height;
    }
  
    @Override /** Return perimeter */
    public double getPerimeter() {
      return 2 * (width + height);
    }

    public String toString() {
        return "\nRectangle: \n" + super.toString() + "\nArea: " + getArea() + "\nPerimeter: " + getPerimeter(); 
    }
  }

class Triangle extends GeometricObject {
	private double sideOne; 
	private double sideTwo; 
	private double sideThree;

	public Triangle(){
	} 

	public Triangle(double sideOne, double sideTwo, double sideThree) {
		this.sideOne = sideOne;
		this.sideTwo = sideTwo;
		this.sideThree = sideThree;
	}

	public Triangle(double sideOne, double sideTwo, double sideThree, 
		String color, boolean filled) {
		this(sideOne, sideTwo, sideThree);
		setColor(color);
		setFilled(filled); 
	}

	public double getsideOne() {
		return sideOne;
	}

	public void setsideOne(double sideOne) {
		this.sideOne = sideOne;
	}

	public double getsideTwo() {
		return sideTwo;
	}

	public void setsideTwo(double sideTwo) {
		this.sideTwo = sideTwo;
	}

	public double getsideThree() {
		return sideThree;
	}

	public void setsideThree(double sideThree) {
		this.sideThree = sideThree;
	}

	@Override
	public double getArea() {
		double s = (sideOne + sideTwo + sideThree) / 2;
		return Math.sqrt(s *(s-sideOne)*(s-sideTwo)*(s-sideThree));
	}

	@Override
	public double getPerimeter() {
		return sideOne + sideTwo + sideThree;
	}

	@Override
	public String toString() {
		return "\nTriangle: \n" + super.toString() + "\nArea: " + getArea() + "\nPerimeter: " + getPerimeter(); 
	}
}

