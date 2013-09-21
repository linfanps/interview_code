import java.util.Vector;

class Observable {
    private boolean changed = false;
    private Vector obs;

    public Observable() {
        obs = new Vector();
    }
    public synchronized void addObserver(Observer o) {
        if (o == null) {
            System.out.println("observer is null");
        } else if (!obs.contains(o)) {
            obs.addElement(o);
        }
    }

    public synchronized void deleteObserver(Observer o) {
        obs.removeElement(o);
    }

    public void setChanged() {
        this.changed = true;
    }
    public void clearChanged() {
        this.changed = false;
    }
    public void notifyObservers() {
        notifyObservers(null);
    }

    public void notifyObservers(Object arg) {
        Object[] allObservers;
        if (!changed) {
            return;
        }
        allObservers = obs.toArray();
        clearChanged();

        for (int i = 0; i < allObservers.length; i++) {
            ((Observer)allObservers[i]).update(this,arg);
        }

    }
}

public class Subject extends Observerable {
    public void doBusinsess() {
        super.setChanged();
        notifyObservers();
    }

    public static void main(String[] args) {
        Subject subject = new Subject();

        Observer mailObserver = new MailObserver();
        Observer smsObserver = new smsObserver();

        subject.add(MailObserver);
        subject.add(smsObserver);

        subject.doBusinsess();
    }
}

interface Observer {
    void update(Observable o, Object arg);

}

class MailObserver implements Observer{

    public void update(Observable o, Object arg) {
        System.out.println("The mail observer has been called");
    }
}

class SMSObserver implements Observer{

    public void update(Observable o, Object arg) {
        System.out.println("The mail observer has been called");
    }
}
