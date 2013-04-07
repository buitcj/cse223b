import org.apache.hadoop.io.ArrayWritable;
import org.apache.hadoop.io.Writable;

public class StringArrayWritable extends ArrayWritable {
	public StringArrayWritable(Class<? extends Writable> valueClass) {
		super(valueClass);
		// TODO Auto-generated constructor stub
	}
}
