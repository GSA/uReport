<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param TicketList $this->ticketList
 *
 * @param string $this->title
 * @param bool $this->disableButtons
 * @param Ticket $this->filterTicket A ticket to leave out of the display
 * @param string $this->moreLink
 */
?>
<div class="ticketList">
	<h2><?php echo $this->title ? View::escape($this->title) : 'Cases'; ?></h2>
	<table>
		<thead>
			<tr><th>Status</th>
				<th>Location</th>
				<th>Entered Date</th>
				<th>Category</th>
				<th></th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->ticketList as $ticket) {
				if ($this->filterTicket
					&& "{$this->filterTicket->getId()}"=="{$ticket->getId()}") {
					continue;
				}
				$status      = View::escape($ticket->getStatus());
				$location    = View::escape($ticket->getLocation());
				$enteredDate = $ticket->getEnteredDate(DATE_FORMAT);

				$category = $ticket->getCategory_id()
					? View::escape($ticket->getCategory()->getName())
					: '';

				if (!$this->disableLinks) {
					$status      = "<a href=\"{$ticket->getURL()}\">$status</a>";
					$location    = "<a href=\"{$ticket->getURL()}\">$location</a>";
					$enteredDate = "<a href=\"{$ticket->getURL()}\">$enteredDate</a>";
					$category    = "<a href=\"{$ticket->getURL()}\">$category</a>";
				}
				echo "
				<tr><td>$status</td>
					<td>$location</td>
					<td>$enteredDate</td>
					<td>$category</td>
					<td>
				";
					if (!$this->disableButtons
							&& userIsAllowed('issues','update')
							&& $ticket->getStatus()!=='closed') {
						$url = new URL(BASE_URL.'/issues/update');
						$url->ticket_id = "{$ticket->getId()}";
						if (isset($_GET['person_id'])) {
							try {
								$person = new Person($_GET['person_id']);
								$url->person_id = "{$person->getId()}";
							}
							catch (Exception $e) {
								// Just ignore invalid people
							}
						}
						echo "<a class=\"add button\" href=\"$url\">Add Issue</a>";
					}
				echo "
					</td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
	<?php
		if ($this->moreLink) {
			echo "<div><a href=\"{$this->moreLink}\">More &gt;&gt;</a></div>";
		}
	?>
</div>
