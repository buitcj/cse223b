import java.io.IOException;
import java.util.Iterator;
import java.util.Vector;

import org.apache.hadoop.conf.*;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.io.WritableComparable;

import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class InvertedIndexer {

	public static void main(String[] args) throws IOException {
		
		Configuration conf = new Configuration();
		Job job = new Job(conf, "InvertedIndexer");
		
		job.setJarByClass(InvertedIndexer.class);
		job.setMapperClass(InvertedIndexer.InvertedIndexMapper.class);
		job.setReducerClass(InvertedIndexer.InvertedIndexReducer.class);

		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);

		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(StringArrayWritable.class);
		
		job.setInputFormatClass(CustomFileInputFormat.class);
		
		//conf.setInputFormatClass(NLinesInputFormat.class);

		if (args.length < 2) {
			System.out.println("ERROR: Wrong number of parameters");
			System.out.println("InvertedIndexer <input_path> <output_path>");
			System.exit(1);
		}

		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		try {
			job.waitForCompletion(true);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static class InvertedIndexMapper extends	Mapper<Text, Text, Text, Text> {
		public void map(Text key, Text val, Context context)
				throws IOException, InterruptedException {
			System.out.println("key: " + key.toString() + " value: " + val);
			context.write(new Text(val.toString()), new Text(key.toString()));
		}
	}
	/*
	 * public static class InvertedIndexReducer extends MapReduceBase implements
	 * Reducer<Text, Text, Text, StringArrayWritable> { public void reduce(Text
	 * key, Iterator<Text> values, OutputCollector<Text, StringArrayWritable>
	 * output, Reporter reporter) throws IOException {
	 * 
	 * StringArrayWritable saw = new StringArrayWritable(Text.class);
	 * Vector<Text> vecText = new Vector<Text>();
	 * 
	 * 
	 * while (values.hasNext()) { vecText.add(values.next()); }
	 * 
	 * Text[] textArray = new Text[vecText.size()]; for(int i = 0; i <
	 * textArray.length; i++) { textArray[i] = vecText.get(i); }
	 * 
	 * saw.set(textArray);
	 * 
	 * output.collect(key, saw.toString()); } }
	 */

	public static class InvertedIndexReducer extends Reducer<Text, Text, Text, Text> {
		public void reduce(Text key, Iterable<Text> values, Context context)
				throws IOException, InterruptedException {

			String paths = "";
			
			Iterator<Text> iter = values.iterator();
			while (iter.hasNext()) {
				paths = paths + iter.next().toString() + ":";
			}

			context.write(key, new Text(paths));
		}
	}
}
