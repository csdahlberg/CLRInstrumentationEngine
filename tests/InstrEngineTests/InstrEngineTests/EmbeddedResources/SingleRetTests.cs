// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System;

namespace SingleRetTests
{
    class Program
    {
        static int Main(string[] args)
        {
            int error = 0;

            error += SingleRetTest("A", "B", "C").Length - 3;

            return error;
        }

        static string SingleRetTest(params string[] values)
        {
            if (values == null)
            {
                throw new ArgumentNullException("values");
            }
            if (values.Length <= 1)
            {
                object obj;
                if (values.Length != 0)
                {
                    obj = values[0];
                    if (obj == null)
                    {
                        return string.Empty;
                    }
                }
                else
                {
                    obj = string.Empty;
                }
                return (string)obj;
            }
            long num = 0L;
            foreach (string text in values)
            {
                if (text != null)
                {
                    num += text.Length;
                }
            }
            if (num > int.MaxValue)
            {
                throw new OutOfMemoryException();
            }
            int num2 = (int)num;
            if (num2 == 0)
            {
                return string.Empty;
            }
            string text2 = new string(' ', num2);
            int num3 = 0;
            foreach (string text3 in values)
            {
                if (!string.IsNullOrEmpty(text3))
                {
                    int length = text3.Length;
                    if (length > num2 - num3)
                    {
                        num3 = -1;
                        break;
                    }
                    FillStringChecked(text2, num3, text3);
                    num3 += length;
                }
            }
            if (num3 != num2)
            {
                return string.Concat((string[])values.Clone());
            }
            return text2;
        }

        private static void FillStringChecked(string dest, int destPos, string src)
        {
        }
    }
}
