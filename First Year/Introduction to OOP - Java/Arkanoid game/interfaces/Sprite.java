package interfaces;
import biuoop.DrawSurface;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public interface Sprite {
    // draw the sprite to the screen
    /**
     * the interface rule is to connect between class that need to
       work accordingly with each other but in every class the Sprite methods
       work differently.
       so with this interface we know to call different objects to do the same methods
       with a different implementaion.
     */

    /**
     * call all the draw on methods in the class that implements this interface.
     * @param d - surface to draw on
     */
    void drawOn(DrawSurface d);
    // notify the sprite that time has passed

    /**
     *call all the timPassed methods in the class that implements this interface.
     */
    void timePassed();
}
