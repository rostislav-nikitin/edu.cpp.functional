using System;
using System.Linq;

namespace transform_vec
{
	class Program
	{
		static void Main(string[] args)
		{
			//Console.WriteLine("Hello World!");
			//TestForArrayLambda((x) => x * x);
			TestForEachArrayLambda((x) => x * x);
		}

		static void TestForArrayLambda(Func<int, int> f)
		{
			int[] source = new int[65535];

			for(int iter = 0; iter < 10000; ++iter)
			{
				for(int i = 0; i < source.Length; ++i)
				{
					source[i] = f(source[i]);
				}
			}
	
		}

		static void TestForEachArrayLambda(Func<int, int> f)
		{
			int[] source = new int[65535];

			for(int iter = 0; iter < 10000; ++iter)
			{
				transform_vec(f, source);
			}
	
		}

		static void transform_vec<T>(Func<T,T> f, T[] source)
		{
			T[] destination = new T[source.Length];
			for(int i = 0; i < source.Length; ++i)
			{
				destination[i] = f(source[i]);
			}
		}
	}
}
