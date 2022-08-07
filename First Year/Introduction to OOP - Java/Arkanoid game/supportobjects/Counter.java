package supportobjects;
/**
 * @author TomerHadar <Tomerh1810@gmail.com>.
 */
public class Counter {

    private int numberOfObject;

    /**
     * constructor that creating new counter with the given parameter.
     * @param number - the first value of the counter object.
     */
    public Counter(int number) {
        this.numberOfObject = number;
    }
    /**
     * add number to current count.
     * @param number - the number to add.
     */
    public void increase(int number) {
        this.numberOfObject += number;
    }
    /**
     * subtract number from current count.
     * @param number - the number to subtract.
     */
    public void decrease(int number) {
        this.numberOfObject -= number;
    }
    /**
     * get current count.
     * @return the current count.
     */
    public int getValue() {
        return this.numberOfObject;
    }

    /**
     * method that set the value of the counter.
     * @param value - the value we want to initialize the counter with it.
     */
    public void setValue(int value) {
        this.numberOfObject = value;
    }
}
