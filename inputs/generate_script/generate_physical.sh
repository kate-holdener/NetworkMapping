#!/bin/bash

D=(1 0.5)
NV=(100 200 300 400 500)
NW=("5-10" "10-20")
EW=("1-5" "5-10" "10-100")

for d in ${D[@]}; do
   for nodes in ${NV[@]}; do
      for nw in ${NW[@]}; do
        for ew in ${EW[@]}; do
           file_name=PN${nodes}_D${d}_NW${nw}_EW${ew}
           ../../GraphGenerator/build/src/graph_generator -density ${d} -nodes ${nodes} -edge_weight ${ew} -node_weight ${node_weight} > physical/${file_name} 
        done
      done
   done
done
