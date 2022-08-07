package animation;
import biuoop.DrawSurface;
import biuoop.Sleeper;
import sprites.SpriteCollection;
import java.awt.Color;

/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */

public class CountdownAnimation implements Animation {
    private double numOfSeconds;
    private int countFrom;
    private boolean stop;
    private long secondsPerFrame;
    private final SpriteCollection gameScreen;

    /**
     * create new object that appear on the screen before the game started and counting 3,2,1
     * and than begin the first stage.
     * @param numOfSeconds -number of seconds that we want the all count last.
     * @param countFrom - the number we count from it until 1.
     * @param gameScreen - object of sprite collection to be able to show the screen of the game
     *                   and make the counting on the game background.
     */
    public CountdownAnimation(double numOfSeconds, int countFrom, SpriteCollection gameScreen) {
        this.numOfSeconds = numOfSeconds;
        this.countFrom = countFrom;
        this.gameScreen = gameScreen;
        this.stop = false;
        this.secondsPerFrame = 0;
        if (countFrom != 0) {
            this.secondsPerFrame = (long) ((numOfSeconds * 1000) / countFrom);
        }
    }
    @Override
    public void doOneFrame(DrawSurface d) {
        this.gameScreen.drawAllOn(d);
        String strNum = Integer.toString(this.countFrom);
        d.setColor(Color.RED);
        d.drawText(d.getWidth() / 2, d.getHeight() / 2, strNum, 40);
        if (this.countFrom != 3) {
            Sleeper sleeper = new Sleeper();
            long startTime = System.currentTimeMillis();
            long usedTime = System.currentTimeMillis() - startTime;
            long milliSecondLeftToSleep = this.secondsPerFrame - usedTime;
            if (milliSecondLeftToSleep > 0) {
                sleeper.sleepFor(milliSecondLeftToSleep);
            }
        }
        if (this.countFrom == 0) {
            this.stop = true;
        }
        this.countFrom -= 1;
    }
    @Override
    public boolean shouldStop() {
        return this.stop;
    }
}
