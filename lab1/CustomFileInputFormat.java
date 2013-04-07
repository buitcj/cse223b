import java.io.IOException;

import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;

public class CustomFileInputFormat extends FileInputFormat<Text, Text> {

	@Override
	public RecordReader<Text, Text> createRecordReader(
			InputSplit is,
			TaskAttemptContext arg1) throws IOException, InterruptedException {
		// TODO Auto-generated method stub

		return new CustomRecordReader(is);
	}
	
	public boolean isSplitable(FileSystem fs, Path filename) 
	{
		return false;
	}
}

