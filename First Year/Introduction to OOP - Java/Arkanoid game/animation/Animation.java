package animation;
import biuoop.DrawSurface;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public interface Animation {
    /**
     * the method is in charge of the logic in the game
     * and do a frame to the animation that we want to run.
     * @param d the surface of the game.
     */
    void doOneFrame(DrawSurface d);

    /**
     * method that indicate the time we need to stop the animation running.
     * @return false if we want the animation to keep running, else return true for stop the animation.
     */
    boolean shouldStop();
}
