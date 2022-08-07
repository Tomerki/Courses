package sprites;
import biuoop.DrawSurface;
import interfaces.Sprite;

import java.util.ArrayList;
import java.util.List;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class SpriteCollection {
    /**
     * priteCollection objects holds a collection of sprites.
     */
    private final ArrayList<Sprite> spritesArray;

    /**
     * constructor that define the field of the new object.
     */
    public SpriteCollection() {
        this.spritesArray = new ArrayList<>();
    }

    /**
     * the function get an object and add it to the sprite array.
     * @param s - a variable from Sprite interface that point on object that implement the sprite interface.
     */
    public void addSprite(Sprite s) {
        this.spritesArray.add(s);
    }
    // call timePassed() on all sprites.

    /**
     *in this function we going with while loop on all the object in the array
      and send an order to make a move.
     */
    public void notifyAllTimePassed() {
        List<Sprite> spritesCopy = new ArrayList<>(this.spritesArray);
        for (Sprite s : spritesCopy) {
            s.timePassed();
        }
    }
    // call drawOn(d) on all sprites.

    /**
     *in this function we going with while loop on all the object in the array
     and send each one of them an order to draw the object on the surface.
     * @param d - some surface to draw on
     */
    public void drawAllOn(DrawSurface d) {
        for (Sprite s : this.spritesArray) {
            s.drawOn(d);
        }
    }
    /**
     * getter function - to have an access to the feild of an object outside the class.
     * @return return the array of the sprites.
     */
    public ArrayList<Sprite> getSpriesArray() {
        return this.spritesArray;
    }
}

















