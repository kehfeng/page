function updateSelectedMedia(element) {
    var selectedMediaContainer = element.closest('.project-media').querySelector('.selected-media');
    var selectedImg = selectedMediaContainer.querySelector('img');
    var selectedVideo = selectedMediaContainer.querySelector('video');
    var newMediaPath = element.getAttribute('data-media');
    var mediaType = element.getAttribute('data-media-type');

    if (mediaType === 'image') {
        // Show selected image
        selectedImg.src = newMediaPath;
        selectedImg.style.display = 'inline'; // Show image
        selectedVideo.style.display = 'none'; // Hide video if exists
    } else if (mediaType === 'video') {
        // Show selected video
        selectedVideo.src = newMediaPath;
        selectedVideo.poster = element.getAttribute('data-poster') || ''; // Set poster if provided
        selectedVideo.style.display = 'inline'; // Show video
        selectedImg.style.display = 'none'; // Hide image if exists

        // Ensure video is loaded before playing
        selectedVideo.addEventListener('loadedmetadata', function() {
            selectedVideo.play().catch(function(error) {
                console.log('Error playing the video:', error);
            });
        });
        selectedVideo.load();
    }
}



// Set default selection to the first image in each project section
document.addEventListener("DOMContentLoaded", function() {
    var projectSections = document.querySelectorAll('.single-project');
    projectSections.forEach(function(section) {
        var firstImage = section.querySelector('.media-selector img');
        updateSelectedMedia(firstImage); // Trigger update for default selection
    });
});
