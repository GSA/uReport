<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Category $this->category
 */
$title = $this->category->getId() ? 'Edit Category' : 'Add Category';

$fields = array(
	'name', 'description', 'postingPermissionLevel', 'displayPermissionLevel',
	'categoryGroup_id', 'department_id'
);
foreach ($fields as $field) {
	$get = 'get'.ucfirst($field);
	$$field = isset($_POST[$field]) ? View::escape($_POST[$field]) : View::escape($this->category->$get());
}

$custom_fields = isset($_POST['custom_fields'])
	? View::escape($_POST['custom_fields'])
	: json_encode($this->category->getCustomFields());
?>

<script>
	$(function(){
		$('#my-form-builder').formbuilder({
			'save_url': 'example-save.php',
			'load_url': 'example-json.php<?php echo '?form_id=' . $_REQUEST['form_id'];?>',
			'useJson' : true
		});
		$(function() {
			$("#my-form-builder ul").sortable({ opacity: 0.6, cursor: 'move'});
		});
	});
</script>

<h1><?php echo $title; ?></h1>
<form method="post" action="<?php echo BASE_URL; ?>/categories/update">
	<fieldset><legend>Category</legend>
		<input name="category_id" type="hidden" value="<?php echo $this->category->getId(); ?>" />
		<table>
			<tr><td><label for="name" class="required">Name</label></td>
				<td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
			</tr>
			<tr><td><label for="categoryGroup_id">Group</label></td>
				<td><select name="categoryGroup_id" id="categoryGroup_id">
					<?php
						$groups = new CategoryGroupList();
						$groups->find();
						foreach ($groups as $group) {
							$selected = $categoryGroup_id==$group->getId()
								? 'selected="selected"'
								: '';
							$name = View::escape($group->getName());
							echo "<option value=\"{$group->getId()}\" $selected>$name</option>";
						}
					?>
					</select>
				</td>
			</tr>
		</table>
		<div>
			<div><label for="description">Description</label></div>
			<textarea name="description" id="description" rows="3" cols="50"><?php echo $description; ?></textarea>
		</div>
		<div>
			<div><label for="department_id">Default Department Assignment</label></div>
			<select name="department_id" id="department_id">
			<?php
				$list = new DepartmentList();
				$list->find();
				foreach ($list as $department) {
					$selected = $department->getId()==$department_id
						? 'selected="selected"'
						: '';
					$name = View::escape($department->getName());
					echo "<option value=\"{$department->getId()}\" $selected >$name</option>";
				}
			?>
			</select>
		</div>

		<button type="submit" class="submit">Submit</button>
		<a class="cancel" href="<?php echo BASE_URL; ?>/categories">Cancel</a>
	</fieldset>
</form>
