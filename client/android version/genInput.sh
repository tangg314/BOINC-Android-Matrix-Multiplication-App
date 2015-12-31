#!/bin/bash

##generates inputA#.xml for work generation
for t in {0..1..1}
do
cat >./inputA$t.xml <<EOL
  <input_template>
    <file_info>
      <number>0</number>
    </file_info>
    <file_info>
      <number>1</number>
    </file_info>
    <file_info>
      <number>2</number>
    </file_info>

    <workunit>
      <file_ref>
        <file_number>0</file_number>
        <open_name>A$t</open_name>
        <copy_file/>
      </file_ref>
      <file_ref>
        <file_number>1</file_number>
        <open_name>B$t</open_name>
        <copy_file/>
      </file_ref>
      <file_ref>
        <file_number>2</file_number>
        <open_name>name</open_name>
        <copy_file/>
      </file_ref>

      <min_quorum>1</min_quorum>
      <target_nresults>1</target_nresults>
      <max_error_results>5</max_error_results>
      <max_success_results>10</max_success_results>
      <max_total_results>15</max_total_results>
      <delay_bound>65536</delay_bound>
    </workunit>
  </input_template>
EOL
cat ./inputA$t.xml
done