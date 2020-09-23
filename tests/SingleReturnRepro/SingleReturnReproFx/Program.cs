using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SingleReturnReproFx
{
    class Program
    {
        static void Main(string[] args)
        {
            string message = string.Concat("Hello", ", ", "World!");
            Console.WriteLine(message);

            Console.WriteLine();
            Console.WriteLine($"Is64BitProcess: {Environment.Is64BitProcess}");

            var envVars = Environment.GetEnvironmentVariables();
            foreach (string envVarKey in envVars.Keys.OfType<string>())
            {
                if (envVarKey.Contains("COR") || envVarKey.Contains("Microsoft"))
                {
                    Console.WriteLine($"{envVarKey}={envVars[envVarKey]}");
                }
            }
        }
    }
}
