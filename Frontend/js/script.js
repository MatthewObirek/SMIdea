
document.addEventListener('DOMContentLoaded', () => {
  const container = document.getElementById('mainContainer');
  const runButton = document.getElementById('runButton');
  const outputDiv = document.getElementById('output');
  const addNewDiscussion = document.getElementById('addNewDiscussion');


  // Backend Post Retrieval 
  runButton.addEventListener('click', async () => {
    try {
      const response = await fetch('/api/hello');
      if (response.ok) {
          const data = await response.text();
          outputDiv.textContent = data;
      } else {
          outputDiv.textContent = 'Error fetching data from the backend.';
      }
    } catch (error) {
      console.error('Error:', error);
      outputDiv.textContent = 'An unexpected error occurred.';
    }
  });


  // For creating new discussions
  addNewDiscussion.addEventListener('click', () => {
    const node = document.createElement('div');
    node.style = 'background: grey;';
    node.className = 'box stack-top';
    node.innerHTML = 'goodby';
    container.appendChild(node);
  });
  // who is there

});