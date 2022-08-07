package animation;
import biuoop.DrawSurface;
import biuoop.GUI;
import biuoop.Sleeper;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class AnimationRunner {
    private final GUI gui;
    private final int framesPerSecond;
    private final Sleeper sleeper;

    /**
     * constructor that create a new object that responsible on running the game.
     */
    public AnimationRunner() {
        this.gui = new GUI("myGame", 800, 600);
        this.framesPerSecond = 60;
        this.sleeper = new Sleeper();
    }

    /**
     * method that run the game with the given animation.
     * @param animation - some animation to run.
     */
    public void run(Animation animation) {
        int millisecondsPerFrame =  1000 / this.framesPerSecond;
        //if shouldStop its true so we stopping the game.
        while (!animation.shouldStop()) {
            long startTime = System.currentTimeMillis(); // timing
            DrawSurface d = this.gui.getDrawSurface();
            animation.doOneFrame(d);
            this.gui.show(d);
            long usedTime = System.currentTimeMillis() - startTime;
            long milliSecondLeftToSleep = millisecondsPerFrame - usedTime;
            if (milliSecondLeftToSleep > 0) {
                this.sleeper.sleepFor(milliSecondLeftToSleep);
            }
        }
    }
    /**
     * getter for the gui.
     * @return the gui.
     */
    public GUI getGui() {
        return this.gui;
    }
}
