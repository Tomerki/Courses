package supportobjects;
import geometry.Point;
import interfaces.Collidable;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class CollisionInfo {
    /**
     * class that hold an information on collision point and the object that fits this collision point.
     */
    private final Point collisionPoint;
    private final Collidable theObject;

    /**
     * constructor that initialize the field of the new object.
     * @param collision - the point value.
     * @param object - the object that the point inside it.
     */
    public CollisionInfo(Point collision, Collidable object) {
        this.collisionPoint = collision;
        this.theObject = object;
    }
    /**
     * getter - to have an access out of the class.
     * @return the point at which the collision occurs.
     */
    public Point collisionPoint() {
        return this.collisionPoint;
    }
    /**
     * getter - to have an access out of the class.
     * @return the collidable object involved in the collision.
     */
    public Collidable collisionObject() {
        return this.theObject;
    }

}







