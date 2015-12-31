#!/bin/bash

##generates outputA0.xml for work generation
echo "<output_template>" >> outputA0.xml
for t in {0..7..1}
do
cat >>./outputA0.xml <<EOL
    <file_info>
      <name><OUTFILE_$t/></name>
      <generated_locally/>
      <upload_when_present/>
      <url><UPLOAD_URL/></url>
      <max_nbytes>50000000</max_nbytes>
    </file_info>
EOL
cat ./outputA0.xml
done

echo "<result>" >> outputA0.xml
for t in {0..7..1}
do
cat >>./outputA0.xml <<EOL
      <file_ref>
        <file_name><OUTFILE_$t/></file_name>
        <open_name>C$t</open_name>
	<copy_file/>
	<no_validate>1</no_validate>
      </file_ref>
EOL
cat ./outputA0.xml
done

echo "</result>" >> outputA0.xml
echo "</output_template>" >> outputA0.xml
    
  
