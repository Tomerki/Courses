package interfaces;

import geometry.Point;
import geometry.Rectangle;
import sprites.Ball;
import supportobjects.Velocity;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public interface Collidable {
    /**
     * with this interface we can send an order for object class's that implement this interface,
     * means, the hit function has a different implements in Paddle class and Block class, but since
     * both of the class implement this interface we can send them an order to go to hit method
     * and objects from different classes will know to go to the methods with the right implement for them.
     */
    /**
     *function that get the closest collision point to the object.
     * @return the rectangle that describe the object we going to collide with.
     */
    Rectangle getCollisionRectangle();
    /**
     * hit have different implements in different classes so its necessary to have a general call to prevent
     * duplicate of parts in the program.
     * @param collisionPoint - the point where the collision occur.
     * @param currentVelocity - the current velocity of the ball that we want to change.
     * @param hitter - the hitter ball in the current collision.
     * @return the new velocity
     */
    Velocity hit(Ball hitter, Point collisionPoint, Velocity currentVelocity);
}


