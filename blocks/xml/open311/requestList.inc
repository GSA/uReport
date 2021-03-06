<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param TicketList $this->ticketList
 */
if (isset($_GET['page']) || isset($_GET['page_size'])) {
	$page      = !empty($_GET['page'])      ? (int)$_GET['page']      : 0;
	$page_size = !empty($_GET['page_size']) ? (int)$_GET['page_size'] : 50;
	$this->ticketList->setPagination($page_size, $page);
}

echo "<service_requests>";
foreach ($this->ticketList as $t) {
	$c = $t->getCategory();
	$service_name = $c ? View::escape($c->getName()) : '';
	$service_code = $c ? $c->getId()   : '';

	$issue = $t->getIssue();
	$description = View::escape($issue->getDescription());

	$history = $t->getHistory();
	$h = end($history);

	$address = View::escape($t->getLocation());
	$zip = View::escape($t->getZip());
	$media = $issue->getMedia();
	$media_url = count($media) ? $media[0]->getURL() : '';

	$agency_responsible = '';
	$p = $t->getAssignedPerson();
	if ($p) {
		$d = $p->getDepartment();
		if ($d) {
			$agency_responsible = View::escape($d->getName());
		}
	}

	echo "
	<request>
		<service_request_id>{$t->getId()}</service_request_id>
		<status>{$t->getStatus()}</status>
		<service_name>$service_name</service_name>
		<service_code>$service_code</service_code>
		<description>$description</description>
		<agency_responsible>$agency_responsible</agency_responsible>
		<requested_datetime>{$t->getEnteredDate('c')}</requested_datetime>
		<updated_datetime>{$h->getEnteredDate('c')}</updated_datetime>
		<address>$address</address>
		<address_id>{$t->getAddressId()}</address_id>
		<zipcode>$zip</zipcode>
		<lat>{$t->getLatitude()}</lat>
		<long>{$t->getLongitude()}</long>
		<media_url>$media_url</media_url>
	</request>
	";
}
echo "</service_requests>";
