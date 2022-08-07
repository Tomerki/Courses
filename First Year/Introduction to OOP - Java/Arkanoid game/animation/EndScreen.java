package animation;
import biuoop.DrawSurface;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class EndScreen implements Animation {
    private final boolean stop;
    private final int numOfBlocks;
    private final int score;

    /**
     * constructor that create a new end screen object.
     * @param numBlocks - to know which string to print, lose or win.
     * @param score - to be able to print the score of the player in the end.
     */
    public EndScreen(int numBlocks, int score) {
        this.stop = false;
        this.numOfBlocks = numBlocks;
        this.score = score;
    }
    @Override
    public void doOneFrame(DrawSurface d) {
        if (this.numOfBlocks == 0) {
            d.drawText(30, d.getHeight() / 2, "You Win! Your score is " + this.score, 32);
        }
        if (this.numOfBlocks > 0) {
            d.drawText(30, d.getHeight() / 2, "Game Over. Your score is " + this.score, 32);
        }
    }
    @Override
    public boolean shouldStop() {
        return this.stop;
    }
}
