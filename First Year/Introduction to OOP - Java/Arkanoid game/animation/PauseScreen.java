package animation;
import biuoop.DrawSurface;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class PauseScreen implements Animation {

    private final boolean stop;

    /**
     * constructor that initialize the field stop to be false, because we want
     * the animation to keep running until the user want to stop and press the "key"
     * that stop the animation.
     */
    public PauseScreen() {
        this.stop = false;
    }
    @Override
    public void doOneFrame(DrawSurface d) {
        d.drawText(10, d.getHeight() / 2, "paused --> press space to continue", 32);
    }
    @Override
    public boolean shouldStop() {
        return this.stop;
    }
}
