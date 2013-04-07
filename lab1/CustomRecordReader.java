import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.util.LineReader;

public class CustomRecordReader extends RecordReader<Text, Text> {
	
	private Text mPath;
	private Text mCurVal = new Text();
	private int curProgress = 0;
	private long mStart = 0;
	private long mEnd = 0;
	private long mPos = 0;
	private LineReader in;
	private int maxLineLength;
	
	public CustomRecordReader(InputSplit fs)
	{
	}

	@Override
	public void close() throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public Text getCurrentKey() throws IOException, InterruptedException {
		return mPath;
	}

	@Override
	public Text getCurrentValue() throws IOException, InterruptedException {
		return mCurVal;
	}

	@Override
	public float getProgress() throws IOException, InterruptedException {
		if (mStart == mEnd) {
            return 0.0f;
        }
        else {
            return Math.min(1.0f, (mPos - mStart) / (float)(mEnd - mStart));
        }
	}

	@Override
	public void initialize(InputSplit split, TaskAttemptContext context)
			throws IOException, InterruptedException {
		
		FileSplit fSplit = (FileSplit) split;
		mPath = new Text(fSplit.getPath().toString());
		
        final Path fileName = fSplit.getPath();
        Configuration conf = context.getConfiguration();
        this.maxLineLength = conf.getInt("mapred.linerecordreader.maxlength",Integer.MAX_VALUE);
        FileSystem fs = fileName.getFileSystem(conf);
        mStart = fSplit.getStart();
        mEnd = mStart + fSplit.getLength();
        FSDataInputStream filein = fs.open(fSplit.getPath());
 
        in = new LineReader(filein,conf);
        
        mPos = mStart;
	}

	@Override
	public boolean nextKeyValue() throws IOException, InterruptedException {
		try
		{
			mCurVal.clear();
			int numRead = in.readLine(mCurVal);
			
			mPos += numRead;
			
			return (numRead == 0 ? false : true);
		}
		catch (Exception e)
		{
			return false;
		}
	}

}

