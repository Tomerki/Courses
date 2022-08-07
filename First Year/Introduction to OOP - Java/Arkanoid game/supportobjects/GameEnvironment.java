package supportobjects;
import geometry.Line;
import geometry.Point;
import interfaces.Collidable;
import java.util.ArrayList;
import java.util.List;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class GameEnvironment {
    // add the given collidable to the environment.
    /**
     * GameEnvironment objects holds a list of Collidable objects(like blocks, paddle).
     */

    private final ArrayList<Collidable> collidesObjects;
    /**
     *constructor that initialize the field of new object.
     */
    public GameEnvironment() {
        this.collidesObjects = new ArrayList<Collidable>();
    }

    /**
     * the function add collidable object to the array.
     * @param c - variable of collidable interface.
     */
    public void addCollidable(Collidable c) {
        this.collidesObjects.add(c);
    }

    /**
     *geter function to have an access out side of the class.
     * @return the collidable objects list.
     */
    public ArrayList<Collidable> getCollidableList() {
        return this.collidesObjects;
    }
    // Assume an object moving from line.start() to line.end().
    // If this object will not collide with any of the collidables
    // in this collection, return null. Else, return the information
    // about the closest collision that is going to occur.

    /**
     * the function first puts in new array the intersection points and then searching the point
       with the minimum distance to the ball. than search for the object and return the information.
     * @param trajectory - line to check the closest collision point of the line to some object in the game(like blocks)
     * @return return a collisionInfo object that hold the object that we going to collide with
       and the collision point.
     */
    public CollisionInfo getClosestCollision(Line trajectory) {
        ArrayList<Point> newArray = new ArrayList<>();
        //two each for loop that puts the collision points in new array.
        List<Collidable> collidableCopy = new ArrayList<Collidable>(this.collidesObjects);
        for (Collidable c : collidableCopy) {
            newArray.addAll(c.getCollisionRectangle().intersectionPoints(trajectory));
        }
        //if array empty its mean no collision so return null.
        if (newArray.isEmpty()) {
            return null;
        }
        //searching closest collision point with minimum distance to the collidable object.
        Point closestPoint = trajectory.findMinDistance(newArray);
        //search the object that the collision point inside him.
        for (Collidable theObject : collidableCopy) {
            if (theObject.getCollisionRectangle().ifPointInsideMe(closestPoint)) {
                return new CollisionInfo(closestPoint, theObject);
            }
        }
        return null;
    }
}




