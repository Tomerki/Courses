package animation;
import biuoop.DrawSurface;
import biuoop.KeyboardSensor;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class KeyPressStoppableAnimation implements Animation {

    private final KeyboardSensor sensor;
    private final Animation animation;
    private final String key;
    private boolean stop;
    private boolean isAlreadyPressed;

    /**
     * constructor that create a new object of KeyPressStoppableAnimation that wait until we press
     * on the "key" to stop the animation.
     * @param sensor - the keyboard sensor of the game.
     * @param strKey - the key we wait for the user to press on.
     * @param animation - the animation that we want to stop when the user press the key.
     */
    public KeyPressStoppableAnimation(KeyboardSensor sensor, String strKey, Animation animation) {
        this.sensor = sensor;
        this.animation = animation;
        this.stop = false;
        this.key = strKey;
        this.isAlreadyPressed = true;
    }
    @Override
    public void doOneFrame(DrawSurface d) {
        animation.doOneFrame(d);
        if (this.sensor.isPressed(this.key)) {
            if (!this.isAlreadyPressed) {
                this.stop = true;
            }
        }
        this.isAlreadyPressed = false;
    }
    @Override
    public boolean shouldStop() {
        return this.stop;
    }
}
