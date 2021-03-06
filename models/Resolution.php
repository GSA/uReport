<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Resolution extends ActiveRecord
{
	protected $tablename = 'resolutions';
	/**
	 * Populates the object with data
	 *
	 * Passing in an associative array of data will populate this object without
	 * hitting the database.
	 *
	 * Passing in a scalar will load the data from the database.
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 *
	 * @param int|array $id
	 */
	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$result = $id;
			}
			else {
				$sql = ActiveRecord::isId($id)
					? 'select * from resolutions where id=?'
					: 'select * from resolutions where name=?';
				$zend_db = Database::getConnection();
				$result = $zend_db->fetchRow($sql, array($id));
			}

			if ($result) {
				$this->data = $result;
			}
			else {
				throw new Exception('resolutions/unknownResolution');
			}
		}
		else {
			// This is where the code goes to generate a new, empty instance.
			// Set any default values for properties that need it here
		}
	}

	public function validate()
	{
		if (!$this->getName()) { throw new Exception('missingRequiredFields'); }
	}

	public function save() { parent::save(); }

	//----------------------------------------------------------------
	// Generic Getters & Setters
	//----------------------------------------------------------------
	public function __toString()     { return parent::get('name');        }
	public function getId()          { return parent::get('id');          }
	public function getName()        { return parent::get('name');        }
	public function getDescription() { return parent::get('description'); }

	public function setName       ($s) { parent::set('name',        $s); }
	public function setDescription($s) { parent::set('description', $s); }

	/**
	 * @param array $post
	 */
	public function handleUpdate($post)
	{
		$this->setName($post['name']);
		$this->setDescription($post['description']);
	}
}
