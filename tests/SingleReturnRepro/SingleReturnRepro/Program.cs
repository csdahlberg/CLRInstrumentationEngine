using System;
using System.Linq;

namespace SingleReturnRepro
{
    class Program
    {
        static void Main(string[] args)
        {
            string message = string.Concat("Hello", ", ", "World!");
            Console.WriteLine(message);

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
