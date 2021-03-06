<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ResolutionList $this->resolutionList
 */
?>
<div class="resolutionList">
	<h1><?php
			if (userIsAllowed('resolutions','update')) {
				echo '<a class="add button" href="'.BASE_URL.'/resolutions/update">Add</a>';
			}
		?>
		Resolutions
	</h1>
	<table>
		<?php
			foreach ($this->resolutionList as $resolution) {
				$editButton = '';
				if (userIsAllowed('resolutions','update')) {
					$editButton = "
					<a class=\"edit button\"
						href=\"".BASE_URL."/resolutions/update?resolution_id={$resolution->getId()}\">
						Edit
					</a>
					";
				}
				$name = View::escape($resolution->getName());
				$description = View::escape($resolution->getDescription());
				echo "
				<tr><td>$editButton</td>
					<td>$name</td>
					<td>$description</td>
				</tr>
				";
			}
		?>
	</table>
</div>