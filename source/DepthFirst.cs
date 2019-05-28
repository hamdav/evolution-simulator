// Depth first search for determining if a graph is coherent

using System;
using System.Linq;
using System.Collections.Generic;

public class DFS{
    public static void Main(){
        //int[][] architecture = new int[][] {new int[] {1,2},new int[] {0},new int[] {0}};
        //int[][] architecture = new int[][] {new int[] {1,2},new int[] {0},new int[] {0,4},new int[] {4}, new int[] {3,2}};
        var architecture = new Dictionary<int,int[]>();
        architecture.Add(5,new int[] {10,100});
        architecture.Add(10,new int[] {5});
        architecture.Add(100,new int[] {5});
        architecture.Add(2,new int[] {});


        if (IsConnected(architecture)){
            Console.WriteLine("Ye mate");
        } 
        else{
            Console.WriteLine("Na mate");
        }

    }
    public static bool IsConnected(Dictionary<int,int[]> graph){
        int n = graph.Count;

        // Alla element i seen borde vara false utom första. 
        var seen = new Dictionary<int,bool>();
        var visited = new Dictionary<int,bool>();
        foreach (int key in graph.Keys){
            seen.Add(key,false);
            visited.Add(key,false);
        }

        int currentNode = graph.Keys.FirstOrDefault();
        seen[currentNode] = true;
        while (true){
            visited[currentNode] = true;

            foreach (int ID in graph[currentNode]){
                seen[ID] = true;
            }
            bool found = false;
            //for (int nextNode = 1; nextNode < n; nextNode++){
            foreach (int nextNode in seen.Keys){
                if (seen[nextNode] && !visited[nextNode]){
                    currentNode = nextNode;
                    found = true;
                    break;
                }
            }
            if (seen.Values.All(x=>x)){
                return true;
            }
            if (!found){
                return false;
            }
        }
    }
    public static bool IsConnected(int[][] graph){
        int n = graph.Length;

        // Alla element i seen borde vara false utom första. 
        bool[] seen = new bool[n];
        seen[0] = true;
        // Alla element i visited borde vara false
        bool[] visited = new bool[n];

        int currentNode = 0;
        while (true){
            visited[currentNode] = true;
            foreach (int ID in graph[currentNode]){
                seen[ID] = true;
            }
            bool found = false;
            for (int nextNode = 1; nextNode < n; nextNode++){
                if (seen[nextNode] && !visited[nextNode]){
                    currentNode = nextNode;
                    found = true;
                    break;
                }
            }
            if (seen.All(x=>x)){
                return true;
            }
            if (!found){
                return false;
            }
        }
    }
}